#include "rev_b.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
/*
    setPinInputHigh(CAPS_PIN);
    setPinInputHigh(SCROLL_PIN);
    setPinInputHigh(NUM_PIN);
    */
    // make sure pins are off by default (bootloader may set these low, led on)
    /*
    setPinOutput(CAPS_PIN);
    writePin(SCROLL_PIN, 1);
    setPinOutput(CAPS_PIN);
    writePin(SCROLL_PIN, 1);
    setPinOutput(NUM_PIN);
    writePin(NUM_PIN, 1);
    */
    matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
/*
    if(res && LOCK_LIGHTS) {

        if(led_state.caps_lock){
            writePin(CAPS_PIN, 0);
        }
        else
            writePin(CAPS_PIN, 1);
        if(led_state.scroll_lock){
            writePin(SCROLL_PIN, 0);
        }
        else
            writePin(SCROLL_PIN, 1);
        if(led_state.num_lock){
            writePin(NUM_PIN, 0);
        }
        else
            writePin(NUM_PIN, 1);

    }
*/
    return res;
}

