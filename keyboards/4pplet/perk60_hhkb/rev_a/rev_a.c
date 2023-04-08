/*
Copyright 2023 Stefan Sundin "4pplet" <4pplet@protonmail.com>

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

#ifdef RGB_MATRIX_ENABLE


const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
    { 0, B_1,  A_1,  C_1 }, // Esc
    { 0, B_2,  A_2,  C_2 }, // 1
    { 0, B_3,  A_3,  C_3 }, // 2
    { 0, B_4,  A_4,  C_4 }, // 3
    { 0, B_5,  A_5,  C_5 }, // 4
    { 0, B_6,  A_6,  C_6 }, // 5
    { 0, B_7,  A_7,  C_7 }, // 6
    { 0, B_8,  A_8,  C_8 }, // 7
    { 0, B_9,  A_9,  C_9 }, // 8
    { 0, B_10, A_10, C_10 }, // 9
    { 0, B_11, A_11, C_11 }, // 0
    { 0, B_12, A_12, C_12 }, // -
    { 0, B_13, A_13, C_13 }, // =
    { 0, B_14, A_14, C_14 }, // /
    { 0, B_15,  A_15,  C_15 }, // `

    { 0, E_2,  D_2,  F_2 }, // Tab
    { 0, E_3,  D_3,  F_3 }, // Q
    { 0, E_4,  D_4,  F_4 }, // W
    { 0, E_5,  D_5,  F_5 }, // E
    { 0, E_6,  D_6,  F_6 }, // R
    { 0, E_7,  D_7,  F_7 }, // T
    { 0, E_8,  D_8,  F_8 }, // Y
    { 0, E_9,  D_9,  F_9 }, // U
    { 0, E_10, D_10, F_10 }, // I
    { 0, E_11, D_11, F_11 }, // O
    { 0, E_12, D_12, F_12 }, // P
    { 0, E_13, D_13, F_13 }, // [
    { 0, E_14, D_14, F_14 }, // ]
    { 0, B_16,  A_16,  C_16 }, // Backspace

    { 0, E_1,  D_1,  F_1 }, // Caps
    { 0, H_4,  G_4,  I_4 }, // A
    { 0, H_5,  G_5,  I_5 }, // S
    { 0, H_6,  G_6,  I_6 }, // D
    { 0, H_7,  G_7,  I_7 }, // F
    { 0, H_8,  G_8,  I_8 }, // G
    { 0, H_9,  G_9,  I_9 }, // H
    { 0, H_10, G_10, I_10 }, // J
    { 0, H_11, G_11, I_11 }, // K
    { 0, H_12, G_12, I_12 }, // L
    { 0, H_13, G_13, I_13 }, // ;
    { 0, H_14, G_14, I_14 }, // '
    { 0, E_15, D_15, F_15 }, // Enter

    { 0, H_2,  G_2,  I_2 }, // Shift
    { 0, H_3,  G_3,  I_3 }, // Z
    { 0, K_3,  J_3,  L_3 }, // X
    { 0, K_4,  J_4,  L_4 }, // C
    { 0, K_6,  J_6,  L_6 }, // V
    { 0, K_7,  J_7,  L_7 }, // B
    { 0, K_9,  J_9,  L_9 }, // N
    { 0, K_10, J_10, L_10 }, // M
    { 0, K_11, J_11, L_11 }, // ,
    { 0, K_13, J_13, L_13 }, // .
    { 0, K_14, J_14, L_14 }, // /
    { 0, H_15, G_15, I_15 }, // Shift
    { 0, E_16, D_16, F_16 }, // Fn

    { 0, H_1,  G_1,  I_1 }, // Ctrl
    { 0, K_1,  J_1,  L_1 }, // Gui
    { 0, K_2,  J_2,  L_2 }, // Alt
    { 0, K_5,  J_5,  L_5 }, // Space
    { 0, K_8,  J_8,  L_8 }, // Space
    { 0, K_12, J_12, L_12 }, // Space
    { 0, K_15, J_15, L_15 }, // Ctrl
    { 0, K_16, J_16, L_16 }, // Gui
    { 0, H_16, G_16, I_16 } // Alt
};

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    if (host_keyboard_led_state().caps_lock && CAPS_LOCK_ENABLE) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (g_led_config.flags[i] & CAPS_LED_GROUP) {
                rgb_matrix_set_color(i, CAPS_LOCK_COLOR);
            }
        }
    }

    return true;
}

#endif
