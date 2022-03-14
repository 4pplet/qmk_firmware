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
#include "rev_a.h"


const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
    /* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |        G location
 *   |  |        |        B location
 *   |  |        |        | */
    { 0, K_16, J_16, L_16 }, //D416 - 0
    { 0, K_15, J_15, L_15 }, //D415 - 1
    { 0, K_14, J_14, L_14 }, //D414 - 2
    { 0, K_13, J_13, L_13 }, //D413 - 3
    { 0, K_12, J_12, L_12 }, //D412 - 4
    { 0, K_11, J_11, L_11 }, //D411 - 5
    { 0, K_10, J_10, L_10 }, //D410 - 6
    { 0, K_9,  J_9,  L_9 }, //D409 - 7
    { 0, K_8,  J_8,  L_8 }, //D408 - 8
    { 0, K_7,  J_7,  L_7 }, //D407 - 9
    { 0, K_6,  J_6,  L_6 }, //D406 - 10
    { 0, K_5,  J_5,  L_5 }, //D405 - 11
    { 0, K_4,  J_4,  L_4 }, //D404 - 12
    { 0, K_3,  J_3,  L_3 }, //D403 - 13
    { 0, K_2,  J_2,  L_2 }, //D402 - 14
    { 0, K_1,  J_1,  L_1 }, //D401 - 15

    { 0, H_16, G_16, I_16 }, //D432 - 16
    { 0, H_15, G_15, I_15 }, //D431 - 17
    { 0, H_14, G_14, I_14 }, //D430 - 18
    { 0, H_13, G_13, I_13 }, //D429 - 19
    { 0, H_12, G_12, I_12 }, //D428 - 20
    { 0, H_11, G_11, I_11 }, //D427 - 21
    { 0, H_10, G_10, I_10 }, //D426 - 22
    { 0, H_9,  G_9,  I_9 }, //D425 - 23
    { 0, H_8,  G_8,  I_8 }, //D424 - 24
    { 0, H_7,  G_7,  I_7 }, //D423 - 25
    { 0, H_6,  G_6,  I_6 }, //D422 - 26
    { 0, H_5,  G_5,  I_5 }, //D421 - 27
    { 0, H_4,  G_4,  I_4 }, //D420 - 28
    { 0, H_3,  G_3,  I_3 }, //D419 - 29
    { 0, H_2,  G_2,  I_2 }, //D418 - 30
    { 0, H_1,  G_1,  I_1 }, //D417 - 31

    { 0, E_15, D_15, F_15 }, //D447 - 32
    { 0, E_14, D_14, F_14 }, //D446 - 33
    { 0, E_15, D_15, F_15 }, //D455 - 34
    { 0, E_12, D_12, F_12 }, //D444 - 35
    { 0, E_11, D_11, F_11 }, //D443 - 36
    { 0, E_10, D_10, F_10 }, //D442 - 37
    { 0, E_9,  D_9,  F_9 }, //D441 - 38
    { 0, E_8,  D_8,  F_8 }, //D440 - 39
    { 0, E_7,  D_7,  F_7 }, //D439 - 40
    { 0, E_6,  D_6,  F_6 }, //D438 - 41
    { 0, E_5,  D_5,  F_5 }, //D437 - 42
    { 0, E_4,  D_4,  F_4 }, //D436 - 43
    { 0, E_3,  D_3,  F_3 }, //D435 - 44
    { 0, E_2,  D_2,  F_2 }, //D434 - 45
    { 0, E_1,  D_1,  F_1 }, //D433 - 46

    { 0, B_16,  A_16,  C_16 }, //D464 - 47
    { 0, B_15,  A_15,  C_15 }, //D463 - 48
    { 0, B_14, A_14, C_14 }, //D462 - 49
    { 0, B_13, A_13, C_13 }, //D461 - 50
    { 0, B_12, A_12, C_12 }, //D460 - 51
    { 0, B_11, A_11, C_11 }, //D459 - 52
    { 0, B_10, A_10, C_10 }, //D458 - 53
    { 0, B_9,  A_9,  C_9 }, //D457 - 54
    { 0, B_8,  A_8,  C_8 }, //D456 - 55
    { 0, B_7,  A_7,  C_7 }, //D455 - 56
    { 0, B_6,  A_6,  C_6 }, //D454 - 57
    { 0, B_4,  A_4,  C_4 }, //D452 - 58
    { 0, B_3,  A_3,  C_3 }, //D451 - 60
    { 0, B_2,  A_2,  C_2 }, //D450 - 61
    { 0, B_1,  A_1,  C_1 } //D449 - 62
};

led_config_t g_led_config = {
    {
    // duplex switch matrix, yay
    {14,12,10,8,6,4,2}, //row1
    {13,11,9,7,5,3,NO_LED}, //row2
    {15,27,25,23,21,19,17}, //row3
    {28,26,24,22,20,18,1}, //row4
    {30,42,40,38,36,34,16}, //row5
    {29,41,39,37,35,33,NO_LED}, //row6
    {31,43,60,58,55,53,NO_LED}, //row7
    {44,61,59,56,54,52,0}, //row8
    {46,62,NO_LED,57,NO_LED,50,32}, //row9
    {45,NO_LED,NO_LED,53,51,49,NO_LED} //row10

    }, {
        { 216,   0 }, { 192,   0 }, { 176,   0 }, { 160,   0 }, { 144,   0 }, { 128,   0 }, { 112,   0 },
        {  96,   0 }, {  80,   0 }, {  64,   0 }, {  48,   0 }, {  32,   0 }, {  16,   0 },
        {   0,   0 }, { 220,  16 }, { 200,  16 }, { 184,  16 }, { 168,  16 }, { 152,  16 }, { 136,  16 },
        { 120,  16 }, { 104,  16 }, {  88,  16 }, {  72,  16 }, {  56,  16 }, {  40,  16 }, {  24,  16 },
        {   4,  16 }, { 214,  32 }, { 188,  32 }, { 172,  32 }, { 156,  32 }, { 140,  32 }, { 124,  32 },
        { 108,  32 }, {  92,  32 }, {  76,  32 }, {  60,  32 }, {  44,  32 }, {  28,  32 },
        {   6,  32 }, { 224,  48 }, { 208,  48 }, { 186,  48 }, { 164,  48 }, { 148,  48 },
        { 132,  48 }, { 116,  48 }, { 100,  48 }, {  84,  48 }, {  68,  48 }, {  52,  48 }, {  36,  48 },
        {   9,  48 }, { 224,  64 }, { 208,  64 }, { 192,  64 }, { 176,  64 },
        { 102,  64 }, {  42,  64 }, {  22,  64 }, {   2,  64 }
    }, {
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1
    }
};

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}

__attribute__ ((weak))
void rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(40, 0xFF, 0xFF, 0xFF);
    }
}

