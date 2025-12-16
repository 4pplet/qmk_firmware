/*
Copyright 2024 Stefan Sundin (4pplet)
Based on HHKB matrix code by Jun Wako <wakojun@gmail.com>

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

#include "matrix.h"
#include "gpio.h"
#include "wait.h"
#include "debug.h"
#include "timer.h"
#include "shkb_stm32.h"

#ifndef SHKB_POST_SCAN_RELAX_US
#define SHKB_POST_SCAN_RELAX_US 75
#endif

static inline bool key_prev_was_on(matrix_row_t matrix[], uint8_t row, uint8_t col) {
    return matrix[row] & (1 << col);
}

void matrix_init_custom(void) {
    dprint("[matrix_init]\n");

    /* Set row/col/enable/prev pins as outputs */
    gpio_set_pin_output(ROW_PIN_0);
    gpio_set_pin_output(ROW_PIN_1);
    gpio_set_pin_output(ROW_PIN_2);
    gpio_set_pin_output(COL_PIN_0);
    gpio_set_pin_output(COL_PIN_1);
    gpio_set_pin_output(COL_PIN_2);
    gpio_set_pin_output(KEY_ENABLE_PIN);
    gpio_set_pin_output(KEY_PREV_PIN);

    /* Set key state as input with pull-up */
    gpio_set_pin_input_high(KEY_STATE_PIN);

    /* Start with enable off (high) and prev off */
    key_strobe_low();
    key_prev_off();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t last_row_value = current_matrix[row];

        key_select_row(row);
        wait_us(SHKB_RELAX_TIME_US);

        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            /* Hysteresis control: assert when previous key state is on */
            if (key_prev_was_on(current_matrix, row, col)) {
                key_prev_on();
            } else {
                key_prev_off();
            }

            /*
             * Critical timing section
             * Disable interrupts to ensure the sensing timing is correct
             */
            chSysLock();

            key_select_col(col);
            key_strobe_high();

            /*
             * Wait for capacitive sensing to stabilize
             * Timing is critical - see hhkb/yang/matrix.c for details
             */
            wait_us(SHKB_ADC_READ_TIME_US);

            if (key_state()) {
                current_matrix[row] &= ~(1 << col);
            } else {
                current_matrix[row] |= (1 << col);
            }

            key_strobe_low();

            chSysUnlock();

            /* Allow matrix voltages to relax */
            wait_us(SHKB_POST_SCAN_RELAX_US);
        }

        if (current_matrix[row] ^ last_row_value) {
            matrix_has_changed = true;
        }
    }

    return matrix_has_changed;
}
