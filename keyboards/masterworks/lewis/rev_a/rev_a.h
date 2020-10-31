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

#include "quantum.h"

#define LAYOUT_all( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k1d, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k2c, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2d, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
    k40, k41, k42, k47, k4b, k4c, k4d  \
) \
{ \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d}, \
    {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d}, \
    {k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d}, \
    {k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d}, \
    {k40, k41, k42, KC_NO, KC_NO, KC_NO, KC_NO, k47, KC_NO, KC_NO, KC_NO, k4b, k4c, k4d}, \
}

#define LAYOUT_ANSI_WKL( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k1d, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k2d, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, \
    k30, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, \
    k40, k42, k47, k4b, k4d  \
) \
{ \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, KC_NO}, \
    {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d}, \
    {k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d}, \
    {k30, KC_NO, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, KC_NO}, \
    {k40, KC_NO, k42, KC_NO, KC_NO, KC_NO, KC_NO, k47, KC_NO, KC_NO, KC_NO, k4b, KC_NO, k4d}, \
}

#define LAYOUT_ISO_WKL( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k1d, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2d, k2c, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, \
    k40, k42, k47, k4b, k4d  \
) \
{ \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, KC_NO}, \
    {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d}, \
    {k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d}, \
    {k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, KC_NO}, \
    {k40, KC_NO, k42, KC_NO, KC_NO, KC_NO, KC_NO, k47, KC_NO, KC_NO, KC_NO, k4b, KC_NO, k4d}, \
}
