# SHKB Pro3

A drop-in replacement controller for the HHKB Professional Classic using STM32F072.

* Keyboard Maintainer: [4pplet](https://github.com/4pplet)
* Hardware Supported: SHKB Pro3 PCB
* Hardware Availability: TBD

## Overview

The SHKB Pro3 interfaces with the HHKB Professional Classic switch board via the 30-pin I-PEX CABLINE-VS connector. It implements the Classic's OpAmp-based capacitive sensing circuit.

| Feature | Specification |
|---------|---------------|
| MCU | STM32F072 |
| Matrix | 4 rows x 15 columns |
| Sensing | OpAmp (OPA2373 on switch board) |
| Connector | 30-pin I-PEX CABLINE-VS |

## Building

Make example for this keyboard (after setting up your build environment):

    make 4pplet/shkb_pro3:default

Flashing example for this keyboard:

    make 4pplet/shkb_pro3:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
