# MCU name
MCU = STM32F103

# Bootloader selection
# BOOTLOADER = vibl
BOOTLOADER = stm32duino

# GENERIC STM32F103C8T6 board - stm32duino bootloader
# OPT_DEFS = -DCORTEX_VTOR_INIT=0x2000
#MCU_LDSCRIPT = STM32F103x8_stm32duino_bootloader
#BOARD = GENERIC_STM32_F103

# OPT_DEFS =
# MCU_LDSCRIPT = STM32F103x8
# BOARD = GENERIC_STM32_F103

## chip/board settings
# the next two should match the directories in
#  <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
#MCU_FAMILY = STM32
#MCU_SERIES = STM32F1xx
# linker script to use
# it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
#  or <this_dir>/ld/
# startup code to use
# is should exist in <chibios>/os/common/ports/ARMCMx/compilers/GCC/mk/
#MCU_STARTUP = stm32f1xx
# it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
# Cortex version
# Teensy LC is cortex-m0; Teensy 3.x are cortex-m4
#MCU  = cortex-m3
# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
#ARMV = 7
DFU_ARGS = -d 6b62:0000 -R

BOOTMAGIC_ENABLE = lite	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
# SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	      # USB Nkey Rollover
RGBLIGHT_ENABLE = yes
# BACKLIGHT_ENABLE = yes
WS2812_DRIVER = spi
ENCODER_ENABLE = yes

# Enter lower-power sleep mode when on the ChibiOS idle thread
# OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
