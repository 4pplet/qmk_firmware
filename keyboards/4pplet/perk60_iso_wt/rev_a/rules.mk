# MCU name
MCU = STM32F411

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no   # Mouse keys
EXTRAKEY_ENABLE = yes   # Audio control and System control
CONSOLE_ENABLE = no    # Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no
RGBLIGHT_ENABLE = no

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE



CIE1931_CURVE = yes


# project specific files
SRC =	keyboards/wilba_tech/wt_main.c \
		keyboards/wilba_tech/wt_rgb_backlight.c \
		drivers/led/issi/is31fl3733.c \
		quantum/color.c \
		i2c_master.c
