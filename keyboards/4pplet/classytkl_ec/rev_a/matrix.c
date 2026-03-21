/*
Copyright 2026 Stefan Sundin "4pplet" <mail@4pplet.com>

EC (electrostatic capacitive) matrix scanning for classyTKL EC.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"
#include "analog.h"
#include "atomic_util.h"
#include "print.h"

static bool     debug_adc_enable = true;
static uint32_t debug_last_print = 0;

/*
 * Pin definitions from schematic:
 *
 * Row drives (active high, accent through 100R series resistors):
 *   PA2=row1  PB5=row2  PB6=row3  PB7=row4  PB8=row5  PB9=row6
 *
 * MUX control (74HC4051):
 *   PB15=MUX_SEL_0(S0)  PB14=MUX_SEL_1(S1)  PB13=MUX_SEL_2(S2)
 *   PA8=MUX_EN_1(~E)    PB12=MUX_EN_2(~E)
 *
 * Sensing:
 *   PA1=ADC_OUT    PA15=DISCHARGE
 *
 * MUX channel -> column mapping (0-based col index):
 *   U402 (MUX_EN_2): ch0->col5, ch1->col0, ch2->col1, ch3->col6,
 *                     ch4->col2, ch5->col4, ch6->col3, ch7->col7
 *   U401 (MUX_EN_1): ch0->col11, ch1->col10, ch2->col9, ch3->col12,
 *                     ch4->col13, ch5->col8, ch6->col14, ch7->col15
 */

/* Row pins */
static const pin_t row_pins[] = {A2, B5, B6, B7, B8, B9};

/* MUX select pins */
#define MUX_SEL_0 B15
#define MUX_SEL_1 B14
#define MUX_SEL_2 B13

/* MUX enable pins (active low) */
#define MUX_EN_1 A8
#define MUX_EN_2 B12

/* Sensing pins */
#define ADC_PIN A1
#define DISCHARGE_PIN A15

/*
 * MUX channel to column index mapping.
 * amux_col_channels[mux][channel] = logical column index
 */
static const uint8_t amux_col_channels[2][8] = {
    /* U402 (MUX_EN_2): ch0-7 -> col indices */
    {5, 0, 1, 6, 2, 4, 3, 7},
    /* U401 (MUX_EN_1): ch0-7 -> col indices */
    {11, 10, 9, 12, 13, 8, 14, 15},
};

static const pin_t mux_en_pins[] = {MUX_EN_2, MUX_EN_1};
static const uint8_t mux_col_count[] = {8, 8};

static adc_mux adc_sense;
static uint16_t noise_floor[MATRIX_ROWS][MATRIX_COLS];

static inline void select_mux_channel(uint8_t ch) {
    gpio_write_pin(MUX_SEL_0, ch & 0x01);
    gpio_write_pin(MUX_SEL_1, ch & 0x02);
    gpio_write_pin(MUX_SEL_2, ch & 0x04);
}

static inline void discharge_capacitor(void) {
    gpio_write_pin_low(DISCHARGE_PIN);
    gpio_set_pin_output(DISCHARGE_PIN);
}

static inline void charge_capacitor(uint8_t row) {
    gpio_set_pin_input(DISCHARGE_PIN);
    gpio_write_pin_high(row_pins[row]);
}

static uint16_t ec_readkey_raw(uint8_t mux, uint8_t row, uint8_t ch) {
    uint16_t sw_value;

    select_mux_channel(ch);

    /* Discharge before read */
    discharge_capacitor();
    gpio_write_pin_low(row_pins[row]);
    wait_us(DISCHARGE_TIME);

    ATOMIC_BLOCK_FORCEON {
        charge_capacitor(row);
        wait_us(4);
        sw_value = adc_read(adc_sense);
    }

    /* Discharge after read */
    discharge_capacitor();
    gpio_write_pin_low(row_pins[row]);
    wait_us(DISCHARGE_TIME);

    return sw_value;
}

static void ec_noise_floor(void) {
    /* Zero out */
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            noise_floor[row][col] = 0;
        }
    }

    /* Sample */
    for (uint8_t sample = 0; sample < NOISE_FLOOR_SAMPLE_COUNT; sample++) {
        for (uint8_t mux = 0; mux < 2; mux++) {
            /* Enable this mux, disable the other */
            gpio_write_pin_high(mux_en_pins[0]);
            gpio_write_pin_high(mux_en_pins[1]);
            gpio_write_pin_low(mux_en_pins[mux]);

            for (uint8_t ch = 0; ch < mux_col_count[mux]; ch++) {
                uint8_t col = amux_col_channels[mux][ch];
                for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                    noise_floor[row][col] += ec_readkey_raw(mux, row, ch);
                }
            }
        }
        wait_ms(5);
    }

    /* Average */
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            noise_floor[row][col] /= NOISE_FLOOR_SAMPLE_COUNT;
        }
    }
}

void matrix_init_custom(void) {
    /* Row pins: output, idle low */
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        gpio_set_pin_output_push_pull(row_pins[i]);
        gpio_write_pin_low(row_pins[i]);
    }

    /* MUX select pins: output */
    gpio_set_pin_output_push_pull(MUX_SEL_0);
    gpio_set_pin_output_push_pull(MUX_SEL_1);
    gpio_set_pin_output_push_pull(MUX_SEL_2);

    /* MUX enable pins: output, both disabled (high) */
    gpio_set_pin_output_push_pull(MUX_EN_1);
    gpio_set_pin_output_push_pull(MUX_EN_2);
    gpio_write_pin_high(MUX_EN_1);
    gpio_write_pin_high(MUX_EN_2);

    /* Discharge pin: start discharged */
    gpio_set_pin_output_push_pull(DISCHARGE_PIN);
    gpio_write_pin_low(DISCHARGE_PIN);

    /* ADC */
    palSetLineMode(ADC_PIN, PAL_MODE_INPUT_ANALOG);
    adc_sense = pinToMux(ADC_PIN);
    adc_read(adc_sense);

    /* Calibrate noise floor */
    ec_noise_floor();

    /* Print noise floor on startup for debugging */
    uprintf("classyTKL EC: init complete\n");
    uprintf("Noise floor:\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uprintf("%4u ", noise_floor[row][col]);
        }
        uprintf("\n");
    }
    uprintf("Threshold: %u\n", EC_ACTUATION_THRESHOLD);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool updated = false;
    bool print_this_cycle = false;

    if (debug_adc_enable && timer_elapsed32(debug_last_print) > 1000) {
        print_this_cycle = true;
        debug_last_print = timer_read32();
    }

    for (uint8_t mux = 0; mux < 2; mux++) {
        /* Enable this mux, disable the other */
        gpio_write_pin_high(mux_en_pins[0]);
        gpio_write_pin_high(mux_en_pins[1]);
        gpio_write_pin_low(mux_en_pins[mux]);

        for (uint8_t ch = 0; ch < mux_col_count[mux]; ch++) {
            uint8_t col = amux_col_channels[mux][ch];

            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                matrix_row_t last = current_matrix[row];
                uint16_t     val  = ec_readkey_raw(mux, row, ch);

                if (print_this_cycle) {
                    uprintf("r%uc%02u:%4u ", row, col, val);
                    if (row == MATRIX_ROWS - 1) uprintf("\n");
                }

                if (val > noise_floor[row][col] + EC_ACTUATION_THRESHOLD) {
                    current_matrix[row] |= (MATRIX_ROW_SHIFTER << col);
                } else {
                    current_matrix[row] &= ~(MATRIX_ROW_SHIFTER << col);
                }

                if (current_matrix[row] != last) {
                    updated = true;
                }
            }
        }
    }

    /* Disable both muxes */
    gpio_write_pin_high(MUX_EN_1);
    gpio_write_pin_high(MUX_EN_2);

    return updated;
}

/*
 * Debug commands (accessible via Magic+key when command mode is enabled):
 *   A - toggle continuous ADC value printing
 *   N - print noise floor values
 */
bool command_extra(uint8_t code) {
    switch (code) {
        case KC_A:
            debug_adc_enable = !debug_adc_enable;
            uprintf("ADC debug: %s\n", debug_adc_enable ? "ON" : "OFF");
            return true;
        case KC_N:
            uprintf("Noise floor:\n");
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                    uprintf("%4u ", noise_floor[row][col]);
                }
                uprintf("\n");
            }
            return true;
        default:
            return false;
    }
}
