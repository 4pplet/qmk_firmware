#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4444
#define PRODUCT_ID      0x0005
#define DEVICE_VER      0x0001
#define MANUFACTURER    4pplet
#define PRODUCT         bootleg-2 Rev A
#define DESCRIPTION     

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15
// ROWS: Top to bottom, COLS: Left to right
#define MATRIX_ROW_PINS {D0,C2,C4,D4,D2}
#define MATRIX_COL_PINS {C5,C6,C7,B7,B6,B5,B4,B3,B2,B1,B0,D6,D5,D3,D1}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define QMK_ESC_OUTPUT C4 // usually COL
#define QMK_ESC_INPUT D0 // usually ROW

