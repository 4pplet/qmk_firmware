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

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"

/*
 * SHKB Pro2 Matrix I/O for STM32
 *
 * Pin assignments for interfacing with HHKB capacitive sensing matrix:
 *
 * row:     3-bit value selects scan row 0-7 (directly drives HC4051 analog mux)
 * col:     3-bit value selects scan col 0-7 (directly drives LS145 decoder)
 * key:     key state input from sensing circuit (active low when pressed)
 * prev:    hysteresis control output, assert high when previous key state was pressed
 * enable:  directly drives LS145 active-low enable (directly drives pin D on LS145)
 *
 * JP variant adds:
 * row_ext: 2-bit row extension for rows 8-15 (selects which HC4051 is active, active low)
 *
 * STM32 Pin Mapping:
 *   PC13 - ROW[0]      Row select bit 0
 *   PC14 - ROW[1]      Row select bit 1
 *   PC15 - ROW[2]      Row select bit 2
 *   PF0  - COL[0]      Column select bit 0
 *   PF1  - COL[1]      Column select bit 1
 *   PA0  - COL[2]      Column select bit 2
 *   PA1  - COL_EN      Column enable (LS145 D, active low)
 *   PA2  - KEY         Key state input
 *   PA3  - PREV        Hysteresis control output
 *   PA4  - ROW_EXT[0]  JP only: row bank 0 select (active low)
 *   PA5  - ROW_EXT[1]  JP only: row bank 1 select (active low)
 */

/* Row select pins (directly drive HC4051 analog mux) */
#define ROW_PIN_0       C13
#define ROW_PIN_1       C14
#define ROW_PIN_2       C15

/* Column select pins (directly drive LS145 decoder) */
#define COL_PIN_0       F0
#define COL_PIN_1       F1
#define COL_PIN_2       A0

/* Column enable (directly drives LS145 pin D, directly enables column scanning) */
#define KEY_ENABLE_PIN  A1

/* Key state input from sensing circuit */
#define KEY_STATE_PIN   A2

/* Hysteresis control output */
#define KEY_PREV_PIN    A3

/* JP-specific row extension pins (directly selects which HC4051 bank is active, active low) */
#define ROW_EXT_PIN_0   A4
#define ROW_EXT_PIN_1   A5

/* Timing configuration */
#ifndef SHKB_RELAX_TIME_US
#define SHKB_RELAX_TIME_US 5
#endif

#ifndef SHKB_ADC_READ_TIME_US
#define SHKB_ADC_READ_TIME_US 5
#endif

/* Common inline functions */
static inline void key_strobe_high(void) {
    gpio_write_pin_low(KEY_ENABLE_PIN);
}

static inline void key_strobe_low(void) {
    gpio_write_pin_high(KEY_ENABLE_PIN);
}

static inline bool key_state(void) {
    return gpio_read_pin(KEY_STATE_PIN);
}

static inline void key_prev_on(void) {
    gpio_write_pin_high(KEY_PREV_PIN);
}

static inline void key_prev_off(void) {
    gpio_write_pin_low(KEY_PREV_PIN);
}

static inline void key_select_row(uint8_t row) {
    gpio_write_pin(ROW_PIN_0, row & 0x01);
    gpio_write_pin(ROW_PIN_1, row & 0x02);
    gpio_write_pin(ROW_PIN_2, row & 0x04);
}

static inline void key_select_col(uint8_t col) {
    gpio_write_pin(COL_PIN_0, col & 0x01);
    gpio_write_pin(COL_PIN_1, col & 0x02);
    gpio_write_pin(COL_PIN_2, col & 0x04);
}

static inline void key_select_row_ext(uint8_t row) {
    /* For JP variant: select which HC4051 bank is active
     * Row 0-7:  ROW_EXT_PIN_0 = 0, ROW_EXT_PIN_1 = 1 (bank 0 active)
     * Row 8-15: ROW_EXT_PIN_0 = 1, ROW_EXT_PIN_1 = 0 (bank 1 active)
     * Directly maps ROW bit 3 to bank selection
     */
    if (row & 0x08) {
        gpio_write_pin_high(ROW_EXT_PIN_0);
        gpio_write_pin_low(ROW_EXT_PIN_1);
    } else {
        gpio_write_pin_low(ROW_EXT_PIN_0);
        gpio_write_pin_high(ROW_EXT_PIN_1);
    }
}
