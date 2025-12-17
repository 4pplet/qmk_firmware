/*
Copyright 2024 Stefan Sundin (4pplet)

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

/* Matrix size: 4 rows x 15 columns (Classic layout) */
#define MATRIX_ROWS 4
#define MATRIX_COLS 15

/* ADC configuration for capacitive sensing */
#define ADC_RESOLUTION ADC_CFGR1_RES_12BIT

/* GPT timer for microsecond delays */
#define SHKB_GPT_DRIVER GPTD3
