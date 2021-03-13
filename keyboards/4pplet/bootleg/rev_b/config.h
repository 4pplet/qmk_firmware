/*
Copyright 2020 Stefan Sundin "4pplet" <4pplet@protonmail.com>

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
#define PRODUCT_ID      0x0006
#define DEVICE_VER      0x0002
#define MANUFACTURER    4pplet
#define PRODUCT         bootleg Rev B

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_COL_PINS { C4, B2, C7, B10, B11, A15, C10, C14, B9, C12, D2, B3, B6, B7, B8 }
#define MATRIX_ROW_PINS { A7, B12, B13, C11, B0 }
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGBLIGHT_ANIMATIONS
#define RGB_DI_PIN B15
#define RGBLED_NUM 16
#define WS2812_SPI SPID2

#define ENCODER_RESOLUTION 2
#define ENCODERS_PAD_A { B5 }
#define ENCODERS_PAD_B { B4 }

#define VIAL_KEYBOARD_UID {0x71, 0xDD, 0x6F, 0x80, 0x44, 0xE7, 0x94, 0x58}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 14 }

#define USB_POLLING_INTERVAL_MS 1

// LED R: A9, LED G: A10, LED B: A8
