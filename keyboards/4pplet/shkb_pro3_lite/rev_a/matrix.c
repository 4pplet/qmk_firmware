/*
Copyright 2026 Stefan Sundin "4pplet" <mail@4pplet.com>

Based on HHKB Classic matrix scanning by Jun Wako and Kan-Ru Chen.

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
#ifdef EC_DEBUG
#    include "print.h"
#endif

/*
 * SHKB Pro3 Lite pin mapping to HHKB switch board.
 *
 * Row drives (active low, idle high):
 *   ROW0 = PA15    ROW1 = PD2     ROW2 = PB3     ROW3 = PB5
 *
 * Alternate row drives for HHKB top PCB variants with different pin
 * mappings. Driven in lockstep with the primary row so the same firmware
 * works regardless of which top PCB is fitted:
 *   ROW1_JP = PB7  (mirrors ROW1)
 *   ROW2_JP = PA1  (mirrors ROW2)
 *
 * Column select (SN74LV4051A mux channel A/B/C):
 *   COL_A = PB4    COL_B = PD1    COL_C = PD3
 *
 * Mux enable (active low):
 *   U1_EN = PD0    U2_EN = PB6
 *
 * Sensing:
 *   OPAMP_EN  = PC14   (active high — enable OpAmp on switch board)
 *   DISCHARGE = PA0    (active high pulse — discharge sample capacitor)
 *   SENSE     = PA2    (ADC input from OpAmp output)
 *
 * Power / indicators:
 *   LDO_ENABLE = PA4   (active high — power to switch board LDO)
 *   LED1       = PB9   (currently unused)
 *   LED2       = PB8   (currently unused)
 */

/* Pin definitions */
#define ROW0_PIN A15
#define ROW1_PIN D2
#define ROW2_PIN B3
#define ROW3_PIN B5

#define ROW1_JP_PIN B7
#define ROW2_JP_PIN A1

#define COL_A_PIN B4
#define COL_B_PIN D1
#define COL_C_PIN D3

#define U1_EN_PIN D0
#define U2_EN_PIN B6

#define OPAMP_EN_PIN C14
#define DISCHARGE_PIN A0
#define SENSE_PIN A2

#define LDO_ENABLE_PIN A4
#define LED1_PIN B9
#define LED2_PIN B8

static const pin_t row_pins[MATRIX_ROWS]    = {ROW0_PIN, ROW1_PIN,    ROW2_PIN,    ROW3_PIN};
static const pin_t row_jp_pins[MATRIX_ROWS] = {NO_PIN,   ROW1_JP_PIN, ROW2_JP_PIN, NO_PIN};

static adc_mux adc_sense;

static inline bool ec_update_cell(matrix_row_t *row_bits, uint8_t col, uint16_t val) {
    bool was_pressed = (*row_bits) & ((matrix_row_t)1 << col);
    uint16_t threshold = was_pressed ? EC_RELEASE_THRESHOLD : EC_PRESS_THRESHOLD;
    bool is_pressed = val > threshold;

    if (is_pressed) {
        *row_bits |= ((matrix_row_t)1 << col);
    } else {
        *row_bits &= ~((matrix_row_t)1 << col);
    }
    return was_pressed != is_pressed;
}

static inline void select_col(uint8_t channel) {
    gpio_write_pin(COL_A_PIN, channel & 0x01);
    gpio_write_pin(COL_B_PIN, channel & 0x02);
    gpio_write_pin(COL_C_PIN, channel & 0x04);
}

static inline void discharge(void) {
    gpio_write_pin_high(DISCHARGE_PIN);
    wait_us(2);
    gpio_write_pin_low(DISCHARGE_PIN);
}

static inline uint16_t sense_key(uint8_t row) {
    /* Drive row low (active) — drive JP pin in lockstep so the same
       firmware works on HHKB top PCB variants that route ROW1/ROW2
       to the alternate pin. */
    gpio_write_pin_low(row_pins[row]);
    if (row_jp_pins[row] != NO_PIN) {
        gpio_write_pin_low(row_jp_pins[row]);
    }
    wait_us(2);

    /* Read ADC */
    uint16_t val = adc_read(adc_sense);

    /* Row back high (idle) */
    gpio_write_pin_high(row_pins[row]);
    if (row_jp_pins[row] != NO_PIN) {
        gpio_write_pin_high(row_jp_pins[row]);
    }

    return val;
}

void matrix_init_custom(void) {
    /* Configure row pins (and their JP alternates, where present) as
       output, idle high */
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        gpio_set_pin_output_push_pull(row_pins[i]);
        gpio_write_pin_high(row_pins[i]);
        if (row_jp_pins[i] != NO_PIN) {
            gpio_set_pin_output_push_pull(row_jp_pins[i]);
            gpio_write_pin_high(row_jp_pins[i]);
        }
    }

    /* Configure column select pins as output */
    gpio_set_pin_output_push_pull(COL_A_PIN);
    gpio_set_pin_output_push_pull(COL_B_PIN);
    gpio_set_pin_output_push_pull(COL_C_PIN);

    /* Configure mux enable pins as output, both disabled (high) */
    gpio_set_pin_output_push_pull(U1_EN_PIN);
    gpio_set_pin_output_push_pull(U2_EN_PIN);
    gpio_write_pin_high(U1_EN_PIN);
    gpio_write_pin_high(U2_EN_PIN);

    /* Configure OpAmp enable as output, disabled */
    gpio_set_pin_output_push_pull(OPAMP_EN_PIN);
    gpio_write_pin_low(OPAMP_EN_PIN);

    /* Configure discharge pin as output, idle low */
    gpio_set_pin_output_push_pull(DISCHARGE_PIN);
    gpio_write_pin_low(DISCHARGE_PIN);

    /* Configure LDO enable as output, power on the switch board */
    gpio_set_pin_output_push_pull(LDO_ENABLE_PIN);
    gpio_write_pin_high(LDO_ENABLE_PIN);

    /* Configure LED pins as output */
    gpio_set_pin_output_push_pull(LED1_PIN);
    gpio_set_pin_output_push_pull(LED2_PIN);
    gpio_write_pin_low(LED1_PIN);
    gpio_write_pin_low(LED2_PIN);

    /* Initialize ADC for sensing */
    palSetLineMode(SENSE_PIN, PAL_MODE_INPUT_ANALOG);
    adc_sense = pinToMux(SENSE_PIN);
    /* Dummy read to initialize ADC driver */
    adc_read(adc_sense);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    /* Enable OpAmp */
    gpio_write_pin_high(OPAMP_EN_PIN);

    /* Scan U1 columns 0-7 */
    gpio_write_pin_low(U1_EN_PIN);   /* Enable U1 */
    gpio_write_pin_high(U2_EN_PIN);  /* Disable U2 */

    for (uint8_t col = 0; col < 8; col++) {
        select_col(col);

        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            discharge();
            uint16_t val = sense_key(row);

            if (ec_update_cell(&current_matrix[row], col, val)) {
                matrix_has_changed = true;
#ifdef EC_DEBUG
                uprintf("[%u,%u] %u %s\n", row, col, val,
                        (current_matrix[row] & ((matrix_row_t)1 << col)) ? "PRESS" : "RELEASE");
#endif
            }
        }
    }

    /* Scan U2 columns 8-14 */
    gpio_write_pin_high(U1_EN_PIN);  /* Disable U1 */
    gpio_write_pin_low(U2_EN_PIN);   /* Enable U2 */

    for (uint8_t col = 8; col < MATRIX_COLS; col++) {
        select_col(col - 8);  /* U2 channels 0-6 */

        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            discharge();
            uint16_t val = sense_key(row);

            if (ec_update_cell(&current_matrix[row], col, val)) {
                matrix_has_changed = true;
#ifdef EC_DEBUG
                uprintf("[%u,%u] %u %s\n", row, col, val,
                        (current_matrix[row] & ((matrix_row_t)1 << col)) ? "PRESS" : "RELEASE");
#endif
            }
        }
    }

    /* Disable both muxes and OpAmp */
    gpio_write_pin_high(U1_EN_PIN);
    gpio_write_pin_high(U2_EN_PIN);
    gpio_write_pin_low(OPAMP_EN_PIN);

    return matrix_has_changed;
}
