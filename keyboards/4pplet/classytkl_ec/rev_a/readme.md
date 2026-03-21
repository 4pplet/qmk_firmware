# Classy TKL EC

Electrostatic capacitive TKL keyboard PCB by 4pplet. Uses OPA350 OpAmp with 74HC4051 analog multiplexers for capacitive key sensing.

* Keyboard Maintainer: [4pplet](https://github.com/4pplet)
* Hardware Supported: Classy TKL EC Rev A (STM32F411CEU6)
* Hardware Availability: [github.com/4pplet/yakiimo-pcb](https://github.com/4pplet/yakiimo-pcb)

Make example for this keyboard (after setting up your build environment):

    make 4pplet/classytkl_ec/rev_a:default

Flashing example for this keyboard:

    make 4pplet/classytkl_ec/rev_a:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader:

* **Physical reset**: Hold the BOOT0 button while pressing the reset button on the PCB
