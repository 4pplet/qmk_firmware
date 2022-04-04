/*
Copyright 2021 Stefan Sundin "4pplet" <4pplet@protonmail.com>

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4444
#define PRODUCT_ID      0x0009
#define DEVICE_VER      0x0001
#define MANUFACTURER    4pplet
#define PRODUCT         Perk60 ISO Rev A

#define MATRIX_ROWS 10
#define MATRIX_COLS 7

#define MATRIX_COL_PINS { A1, B12, B14, A2, A0, A3, A4}
#define MATRIX_ROW_PINS { C14, C13, B5, B4, B8, A15, B3, B9, A5, A7}
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

#define DRIVER_ADDR_1 0b1010000
#define DRIVER_COUNT 1
#define DRIVER_1_LED_TOTAL 62
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL

#define STM32_HSECLK 8000000
