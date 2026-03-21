# SHKB Pro3 Lite

HHKB replacement controller PCB by 4pplet. Interfaces with the original HHKB switch board via the 30-pin I-PEX connector for capacitive (Topre) key sensing.

* Keyboard Maintainer: [4pplet](https://github.com/4pplet)
* Hardware Supported: SHKB Pro3 Lite Rev A (STM32G0B1CBT6)
* Hardware Availability: [github.com/4pplet/SHKB](https://github.com/4pplet/SHKB)

Make example for this keyboard (after setting up your build environment):

    make 4pplet/shkb_pro3_lite/rev_a:default

Flashing example for this keyboard:

    make 4pplet/shkb_pro3_lite/rev_a:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader:

* **Physical reset**: Hold the BOOT0 button while pressing the reset button on the PCB
