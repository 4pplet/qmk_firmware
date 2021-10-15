#pragma once

#include "quantum.h"

/* LAYOUT_all
 * ┌────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬──────┐
 * │00  │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d    │
 * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
 * │10    │11 │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │    │
 * ├──────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐1d │
 * │20     │21 │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │   │
 * ├─────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
 * │30   │31 │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3c   │3d │
 * ├─────┼───┴┬──┴──┬┴───┴───┴─┬─┴─┬─┴───┴───┴┬──┴──┬┴───┬─┴───┤
 * │40   │41  │43   │44        │45 │46        │48   │4a  │4b   │
 * └─────┴────┴─────┴──────────┴───┴──────────┴─────┴────┴─────┘
 */
#define LAYOUT_all( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k1d, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
    k40, k41, k43,      k44,      k45,      k46,           k48, k4a, k4b  \
) \
{ \
    {k00, k01, k02,   k03, k04, k05, k06, k07,   k08, k09,   k0a, k0b, k0c,     k0d},  \
    {k10, k11, k12,   k13, k14, k15, k16, k17,   k18, k19,   k1a, k1b, k1c,     k1d},  \
    {k20, k21, k22,   k23, k24, k25, k26, k27,   k28, k29,   k2a, k2b, k2c,     KC_NO},\
    {k30, k31, k32,   k33, k34, k35, k36, k37,   k38, k39,   k3a, k3b, k3c,     k3d},  \
    {k40, k41, KC_NO, k43, k44, k45, k46, KC_NO, k48, KC_NO, k4a, k4b, KC_NO,   KC_NO} \
}

#define LAYOUT_aek( \
    k00, k01, k02,    k03, k04, k05, k06, k07,   k08, k09,   k0a, k0b, k0c,     k0d, \
    k10, k11, k12,    k13, k14, k15, k16, k17,   k18, k19,   k1a, k1b, k1c,     k1d, \
    k20, k21, k22,    k23, k24, k25, k26, k27,   k28, k29,   k2a, k2b, k2c,          \
    k30, k31, k32,    k33, k34, k35, k36, k37,   k38, k39,   k3a, k3b, k3c,          \
    k40, k41, k43,    k45,                                   k48, k4a, k4b           \
) \
{ \
    {k00, k01, k02,   k03, k04, k05, k06, k07,   k08, k09,   k0a, k0b, k0c,     k0d},  \
    {k10, k11, k12,   k13, k14, k15, k16, k17,   k18, k19,   k1a, k1b, k1c,     k1d},  \
    {k20, k21, k22,   k23, k24, k25, k26, k27,   k28, k29,   k2a, k2b, k2c,     KC_NO},\
    {k30, k31, k32,   k33, k34, k35, k36, k37,   k38, k39,   k3a, k3b, k3c,     KC_NO},  \
    {k40, k41, KC_NO, k43, KC_NO, k45, KC_NO, KC_NO, k48, KC_NO, k4a, k4b, KC_NO, KC_NO} \
}
