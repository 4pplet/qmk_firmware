// Copyright 2024 Stefan Sundin (4pplet)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * HHKB Classic Layout (60 keys, 4x15 matrix)
     *
     * Matrix scan order (from reverse engineering):
     *         Col: 0   1   2   3   4   5   6   7   8   9   10  11  12  13  14
     * Row 0:       LSh z   x   LAl LGu f   spc n   ,   .   RGu m   /   RAl RSh
     * Row 1:       Esc 2   3   1   4   5   6   7   9   0   -   8   =   `   \
     * Row 2:       Tab w   e   q   r   t   g   y   i   o   p   u   [   Del ]
     * Row 3:       Ctl s   d   a   c   v   b   h   k   l   ;   j   '   Fn  Ret
     *
     * Physical layout:
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Del  |
     * |-----------------------------------------------------------|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn |
     * |-----------------------------------------------------------|
     * |    |LAl|LGu|       Space           |RGu|RAl|              |
     * `-----------------------------------------------------------'
     */
    [0] = LAYOUT(
        KC_LSFT, KC_Z,    KC_X,    KC_LALT, KC_LGUI, KC_F,    KC_SPC,  KC_N,    KC_COMM, KC_DOT,  KC_RGUI, KC_M,    KC_SLSH, KC_RALT, KC_RSFT,
        KC_ESC,  KC_2,    KC_3,    KC_1,    KC_4,    KC_5,    KC_6,    KC_7,    KC_9,    KC_0,    KC_MINS, KC_8,    KC_EQL,  KC_GRV,  KC_BSLS,
        KC_TAB,  KC_W,    KC_E,    KC_Q,    KC_R,    KC_T,    KC_G,    KC_Y,    KC_I,    KC_O,    KC_P,    KC_U,    KC_LBRC, KC_DEL,  KC_RBRC,
        KC_LCTL, KC_S,    KC_D,    KC_A,    KC_C,    KC_V,    KC_B,    KC_H,    KC_K,    KC_L,    KC_SCLN, KC_J,    KC_QUOT, MO(1),   KC_ENT
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_PWR,  KC_F2,   KC_F3,   KC_F1,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F9,   KC_F10,  KC_F11,  KC_F8,   KC_F12,  KC_INS,  KC_DEL,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_UP,   KC_PAUS, _______, _______, _______,
        _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, _______, KC_PAST, KC_HOME, KC_PGUP, KC_LEFT, KC_PSLS, KC_RGHT, _______, _______
    )
};
