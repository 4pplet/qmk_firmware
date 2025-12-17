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

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"

/*
 * SHKB Pro3 Matrix I/O for STM32F072
 *
 * Drop-in replacement controller for HHKB Professional Classic.
 * Interfaces with the Classic's 30-pin I-PEX CABLINE-VS connector.
 *
 * Matrix: 4 rows x 15 columns
 * Sensing: OpAmp-based capacitive sensing (OPA2373 on switch board)
 *
 * Connector signals:
 *   ROW0-3      Direct row drive for capacitive sensing
 *   ROW1_JP/ROW2_JP  Additional rows for JP variant
 *   COL_A/B/C   3-bit column select for two HC4051 muxes
 *   U1_EN       Column mux U1 enable (active low, columns 0-7)
 *   U2_EN       Column mux U2 enable (active low, columns 8-14)
 *   OPAMP_EN    OpAmp enable
 *   DISCHARGE   Capacitor discharge control
 *   LDO_EN      LDO enable for main board power
 *   LED1/LED2   Status LEDs
 *   RGB_DATA    WS2812 RGB LED data
 */

/* Row drive pins */
#define ROW0_PIN    A15
#define ROW1_PIN    B5
#define ROW2_PIN    B7
#define ROW3_PIN    B9

/* JP variant additional row pins */
#define ROW1_JP_PIN C14
#define ROW2_JP_PIN A4

/* Column select pins (accent two HC4051 muxes on switch board) */
#define COL_A_PIN   B8
#define COL_B_PIN   B4
#define COL_C_PIN   B6

/* Column mux enable pins (active low) */
#define U1_EN_PIN   B3      /* Enables columns 0-7 */
#define U2_EN_PIN   C13     /* Enables columns 8-14 */

/* OpAmp control */
#define OPAMP_EN_PIN    A1
#define DISCHARGE_PIN   A3

/* Sense input (analog from OpAmp) - ADC IN0 */
#define SENSE_PIN       A0

/* Unknown pins from connector */
#define UNKNOWN1_PIN    A2      /* PA2 - unknown function */
#define UNKNOWN2_PIN    F1      /* PF1 - unknown function */

/* LDO enable for main board power */
#define LDO_EN_PIN      A5

/* LED pins */
#define LED1_PIN    F0
#define LED2_PIN    C15

/* RGB LED data */
#define RGB_DATA_PIN    A8

/* Timing configuration (microseconds) */
#define SHKB_PRO3_ROW_DRIVE_US      20      /* Row drive pulse width */
#define SHKB_PRO3_ROW_SETTLE_US     80      /* Time between row drives */
#define SHKB_PRO3_OPAMP_EN_US       22      /* OpAmp enable time */
#define SHKB_PRO3_DISCHARGE_US      7       /* Capacitor discharge time */
#define SHKB_PRO3_SENSE_THRESHOLD   0x80    /* TODO: Calibrate - threshold for key press */
