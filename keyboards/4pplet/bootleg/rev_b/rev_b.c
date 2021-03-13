#include "rev_b.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    setPinOutput(CAPS_PIN);
    setPinOutput(SCROLL_PIN);
    setPinOutput(NUM_PIN);
    matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res && LOCK_LIGHTS) {
        writePin(CAPS_PIN, led_state.caps_lock);
        writePin(SCROLL_PIN, led_state.scroll_lock);
        writePin(NUM_PIN, led_state.num_lock);
    }
    return res;
}
