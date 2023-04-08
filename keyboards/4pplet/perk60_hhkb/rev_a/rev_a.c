/*
Copyright 2022 Stefan Sundin "4pplet" <4pplet@protonmail.com>

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
#include "rev_a.h"

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
    { 0, K_16, J_16, L_16 } // Gui
    { 0, H_16, G_16, I_16 }, // Alt
};

led_config_t g_led_config = {
    {
    #define XXX NO_LED

    {   0,   2,   4,   6,   8,  10,  12 },
    {   1,   3,   5,   7,   9,  11, XXX },
    {  14,  16,  18,  20,  22,  24,  26 },
    {  15,  17,  19,  21,  23,  25,  13 },
    {  28,  30,  32,  34,  36,  38,  40 },
    {  29,  31,  33,  35,  37,  39, XXX },
    {  41,  43,  45,  47,  49,  51, XXX },
    {  42,  44,  46,  48,  50,  52,  27 },
    {  54,  55, XXX,  57, XXX,  60,  53 },
    {  56, XXX, XXX,  58,  59,  61, XXX },

    }, {
{  0,0  }, { 16,0  }, { 32,0  }, { 48,0  }, { 64,0  }, { 80,0  }, { 96,0  }, {112,0  }, {128,0  }, {144,0  },
{160,0  }, {176,0  }, {192,0  }, {208,0  }, {224,0  }, {  4,16 }, { 24,16 }, { 40,16 }, { 56,16 }, { 72,16 },
{ 88,16 }, {104,16 }, {120,16 }, {136,16 }, {152,16 }, {168,16 }, {184,16 }, {200,16 }, {220,16 }, {  6,32 },
{ 28,32 }, { 44,32 }, { 60,32 }, { 76,32 }, { 92,32 }, {108,32 }, {124,32 }, {140,32 }, {156,32 }, {172,32 },
{188,32 }, {214,32 }, { 10,48 }, { 36,48 }, { 52,48 }, { 68,48 }, { 84,48 }, {100,48 }, {116,48 }, {132,48 },
{148,48 }, {164,48 }, {180,48 }, {202,48 }, {224,48 }, {  4,64 }, { 24,64 }, { 44,64 }, { 80,64 }, {112,64 },
{144,64 }, {180,64 }, {200,64 }, {220,64 },
    }, {
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 1, 4, 4, 4, 1, 1, 1
    }
};
__attribute__((weak)) void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock && CAPS_LOCK_ENABLE) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (g_led_config.flags[i] & CAPS_LED_GROUP) {
                rgb_matrix_set_color(i, CAPS_LOCK_COLOR);
            }
        }
    }
}
#endif
