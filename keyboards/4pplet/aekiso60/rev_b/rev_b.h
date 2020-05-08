#pragma once

#include "quantum.h"

#define CAPSLOCK_INDICATOR true // indicate capslock, scroll lock etc with rgb led

#define BRIGHTNESS_LEVELS 10
#define DEFAULT_BRIGHTNESS_LEVEL 5

#define TIMER_TOP 0xFFFFU

bool led_update_kb(led_t led_state);
bool led_update_user(led_t led_state);
void keyboard_pre_init_user(void);
void caps_led_set(bool on);
void init_led(void);
uint16_t cie_lightness(uint16_t v);

// variables
uint16_t brightness_level;

#define LAYOUT_all( \
    k00, k01, k02,    k03, k04, k05, k06, k07,   k08, k09,   k0a, k0b, k0c,     k4c, \
    k10, k11, k12,    k13, k14, k15, k16, k17,   k18, k19,   k1a, k1b, k1c,     k4b, \
    k20, k21, k22,    k23, k24, k25, k26, k27,   k28, k29,   k2a, k2b, k2c,          \
    k30, k31, k32,    k33, k34, k35, k36, k37,   k38, k39,   k3a, k3b, k3c,     k4a, \
    k40, k41, k43,    k44, k45, k46, k47, k48,   k49                                 \
) \
{ \
    {k00, k01, k02,   k03, k04, k05, k06, k07,   k08, k09,   k0a, k0b, k0c,     },  \
    {k10, k11, k12,   k13, k14, k15, k16, k17,   k18, k19,   k1a, k1b, k1c,     },  \
    {k20, k21, k22,   k23, k24, k25, k26, k27,   k28, k29,   k2a, k2b, k2c,     },\
    {k30, k31, k32,   k33, k34, k35, k36, k37,   k38, k39,   k3a, k3b, k3c,     },  \
    {k40, k41, KC_NO, k43, k44, k45, k46, k47,   k48, k49,   k4a, k4b, k4c } \
}

