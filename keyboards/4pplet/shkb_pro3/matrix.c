/*
Copyright 2024 Stefan Sundin (4pplet)

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

/*
 * SHKB Pro3 Matrix Scanning
 *
 * This implements the HHKB Professional Classic sensing sequence:
 *
 * For each column (0-14):
 *   1. Select column via COL_A/B/C and U1_EN or U2_EN
 *   2. For each row (0-3):
 *      a. Enable OpAmp
 *      b. Discharge sample capacitor
 *      c. Drive row high (20us pulse)
 *      d. Read sense signal via ADC
 *      e. Disable OpAmp
 *
 * Matrix layout (from reverse engineering):
 *
 *         U1                              U2
 *         Y0  Y1  Y2  Y3  Y4  Y5  Y6  Y7  Y0  Y1  Y2  Y3  Y4  Y5  Y6
 *         0   2   3   1   4   5   6   7   9   a   b   8   c   e   d
 *         -----------------------------------------------------------
 * ROW0    LSh z   x   LAl LGu f   spc n   ,   .   RGu m   /   RAl RSh
 * ROW1    Esc 2   3   1   4   5   6   7   9   0   -   8   =   `   \
 * ROW2    Tab w   e   q   r   t   g   y   i   o   p   u   [   Del ]
 * ROW3    Ctl s   d   a   c   v   b   h   k   l   ;   j   '   Fn  Ret
 */

#include "matrix.h"
#include "gpio.h"
#include "wait.h"
#include "debug.h"
#include "print.h"
#include "shkb_pro3.h"

/* STM32 ADC registers - direct access for speed */
#include "hal.h"

/* Default actuation threshold (12-bit ADC, lower = pressed) */
#ifndef SHKB_PRO3_ACTUATION_THRESHOLD
#define SHKB_PRO3_ACTUATION_THRESHOLD 1375
#endif

/* Column to mux mapping
 * Columns 0-7: U1 (enable via U1_EN low)
 * Columns 8-14: U2 (enable via U2_EN low)
 */
static inline void select_column(uint8_t col) {
    uint8_t mux_addr;

    if (col < 8) {
        /* U1: columns 0-7 */
        mux_addr = col;
        gpio_write_pin_low(U1_EN_PIN);
        gpio_write_pin_high(U2_EN_PIN);
    } else {
        /* U2: columns 8-14 */
        mux_addr = col - 8;
        gpio_write_pin_high(U1_EN_PIN);
        gpio_write_pin_low(U2_EN_PIN);
    }

    /* Set 3-bit column address */
    gpio_write_pin(COL_A_PIN, mux_addr & 0x01);
    gpio_write_pin(COL_B_PIN, mux_addr & 0x02);
    gpio_write_pin(COL_C_PIN, mux_addr & 0x04);
}

static inline void deselect_columns(void) {
    /* Disable both muxes */
    gpio_write_pin_high(U1_EN_PIN);
    gpio_write_pin_high(U2_EN_PIN);
}

static inline void drive_row(uint8_t row, bool state) {
    switch (row) {
        case 0: gpio_write_pin(ROW0_PIN, state); break;
        case 1: gpio_write_pin(ROW1_PIN, state); break;
        case 2: gpio_write_pin(ROW2_PIN, state); break;
        case 3: gpio_write_pin(ROW3_PIN, state); break;
    }
}

static inline void opamp_enable(void) {
    gpio_write_pin_high(OPAMP_EN_PIN);
}

static inline void opamp_disable(void) {
    gpio_write_pin_low(OPAMP_EN_PIN);
}

static inline void discharge_capacitor(void) {
    gpio_write_pin_high(DISCHARGE_PIN);
    wait_us(SHKB_PRO3_DISCHARGE_US);
    gpio_write_pin_low(DISCHARGE_PIN);
}

/* Read ADC value from SENSE pin (PA0 = ADC channel 0) */
static inline uint16_t adc_read(void) {
    /* Start ADC conversion */
    ADC1->CR |= ADC_CR_ADSTART;

    /* Wait for conversion to complete */
    while (!(ADC1->ISR & ADC_ISR_EOC));

    /* Return 12-bit result */
    return ADC1->DR;
}

/* Check if key is pressed based on ADC threshold */
static inline bool sense_key(void) {
    uint16_t adc_value = adc_read();
    /* Lower ADC value = key pressed (capacitance increases) */
    return adc_value < SHKB_PRO3_ACTUATION_THRESHOLD;
}

void matrix_init_custom(void) {
    dprint("[matrix_init]\n");

    /* Row pins as outputs, initially low */
    gpio_set_pin_output(ROW0_PIN);
    gpio_set_pin_output(ROW1_PIN);
    gpio_set_pin_output(ROW2_PIN);
    gpio_set_pin_output(ROW3_PIN);
    gpio_write_pin_low(ROW0_PIN);
    gpio_write_pin_low(ROW1_PIN);
    gpio_write_pin_low(ROW2_PIN);
    gpio_write_pin_low(ROW3_PIN);

    /* Column select pins as outputs */
    gpio_set_pin_output(COL_A_PIN);
    gpio_set_pin_output(COL_B_PIN);
    gpio_set_pin_output(COL_C_PIN);

    /* Mux enable pins as outputs, initially disabled (high) */
    gpio_set_pin_output(U1_EN_PIN);
    gpio_set_pin_output(U2_EN_PIN);
    gpio_write_pin_high(U1_EN_PIN);
    gpio_write_pin_high(U2_EN_PIN);

    /* OpAmp control */
    gpio_set_pin_output(OPAMP_EN_PIN);
    gpio_set_pin_output(DISCHARGE_PIN);
    gpio_write_pin_low(OPAMP_EN_PIN);
    gpio_write_pin_low(DISCHARGE_PIN);

    /* LED pins as outputs, initially off */
    gpio_set_pin_output(LED1_PIN);
    gpio_set_pin_output(LED2_PIN);
    gpio_write_pin_high(LED1_PIN);
    gpio_write_pin_high(LED2_PIN);

    /* LDO enable for main board power - enable it */
    gpio_set_pin_output(LDO_EN_PIN);
    gpio_write_pin_high(LDO_EN_PIN);

    /* Initialize ADC for SENSE pin (PA0 = ADC channel 0)
     * Configure for 12-bit resolution, continuous mode
     */
    /* Enable ADC clock */
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    /* Ensure ADC is disabled before configuration */
    ADC1->CR &= ~ADC_CR_ADEN;

    /* Configure ADC:
     * - 12-bit resolution (default)
     * - Continuous conversion mode
     * - Right-aligned data
     */
    ADC1->CFGR1 = ADC_CFGR1_CONT;

    /* Set sampling time (longest for stability) */
    ADC1->SMPR = ADC_SMPR_SMP_0 | ADC_SMPR_SMP_1 | ADC_SMPR_SMP_2; /* 239.5 cycles */

    /* Select channel 0 (PA0) */
    ADC1->CHSELR = ADC_CHSELR_CHSEL0;

    /* Calibrate ADC */
    ADC1->CR |= ADC_CR_ADCAL;
    while (ADC1->CR & ADC_CR_ADCAL);

    /* Enable ADC */
    ADC1->CR |= ADC_CR_ADEN;
    while (!(ADC1->ISR & ADC_ISR_ADRDY));

    dprint("[ADC initialized]\n");
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        select_column(col);

        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            matrix_row_t last_row_value = current_matrix[row];

            /* Classic sensing sequence */
            chSysLock();

            opamp_enable();
            wait_us(SHKB_PRO3_OPAMP_EN_US);

            discharge_capacitor();

            drive_row(row, true);
            wait_us(SHKB_PRO3_ROW_DRIVE_US);

            if (sense_key()) {
                current_matrix[row] |= (1 << col);
            } else {
                current_matrix[row] &= ~(1 << col);
            }

            drive_row(row, false);
            opamp_disable();

            chSysUnlock();

            wait_us(SHKB_PRO3_ROW_SETTLE_US);

            if (current_matrix[row] != last_row_value) {
                matrix_has_changed = true;
            }
        }
    }

    deselect_columns();

    return matrix_has_changed;
}
