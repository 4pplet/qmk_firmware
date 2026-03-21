/*
Copyright 2026 Stefan Sundin "4pplet" <mail@4pplet.com>

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

#define MATRIX_ROWS 4
#define MATRIX_COLS 15

/* ADC resolution: 12-bit for better capacitive sensing precision */
#define ADC_RESOLUTION ADC_CFGR1_RES_12BIT

/* GPT timer for accurate wait_us() on Cortex-M0+ */
#define WAIT_US_TIMER GPTD3

/* Default actuation threshold (ADC value, 12-bit range 0-4095) */
#define EC_ACTUATION_THRESHOLD 1375

/* Debounce is set to default (5) via keyboard.json */
