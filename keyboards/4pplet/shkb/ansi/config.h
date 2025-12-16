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

/* ANSI matrix size: 8 rows x 8 cols = 60 keys */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

/* ANSI relaxation timing (75us like original HHKB ANSI) */
#define SHKB_RELAX_TIME_US 5
#define SHKB_POST_SCAN_RELAX_US 75
