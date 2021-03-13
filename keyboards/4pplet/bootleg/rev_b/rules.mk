# MCU name
MCU = STM32F103

# Bootloader selection
# BOOTLOADER = vibl
BOOTLOADER = stm32duino

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
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
