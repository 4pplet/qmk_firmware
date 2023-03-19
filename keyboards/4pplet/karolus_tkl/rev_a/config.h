/*
Copyright 2023 Stefan Sundin "4pplet" <mail@4pplet.com>

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

// ROWS: Top to bottom, COLS: Left to right
#define MATRIX_ROW_PINS {B11,B10,B1,B2,B0,A7,A4,A5,A1,A0,B4,B3}
#define MATRIX_COL_PINS {C13,C14,C15,F1,F0,B5,A15,A6,A3}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
