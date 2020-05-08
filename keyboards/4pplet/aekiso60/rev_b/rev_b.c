#include "rev_b.h"

#define ON true
#define OFF false

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.
  init_led();
}

void init_led(void){
  // Set on match, clear on TOP
  TCCR1A  = ((1 << COM1B1)| (1 << COM1B0)); // all leds on.
  // Phase + Frequency Correct PWM, Fcpu speed
  TCCR1B  = ((1 << CS10) | (1 << WGM13));
  // define end of timer
  ICR1 = TIMER_TOP;
  // default set to lowest, will not toggle
  led_set(OFF);

  brightness_level = DEFAULT_BRIGHTNESS_LEVEL;
  // Set our LED pin as output
  setPinOutput(C5);
}

bool led_update_user(led_t led_state) {
/*
By convention, return true from led_update_user() to get the led_update_kb() hook to run its code,
and return false when you would prefer not to run the code in led_update_kb().
*/
  if(CAPSLOCK_INDICATOR)
    return true;
  else
    return false;
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        if(led_state.caps_lock)
          led_set(ON);
        else
          led_set(OFF);
    }
    return res;
}

void caps_led_set(bool on){
    uint32_t base_brightness = cie_lightness(TIMER_TOP * (uint32_t)brightness_level / BRIGHTNESS_LEVELS);
    OCR1B = (uint32_t)on * (uint32_t)base_brightness / 0xFF;
}
// See http://jared.geek.nz/2013/feb/linear-led-pwm
uint16_t cie_lightness(uint16_t v) {
    if (v <= 5243)     // if below 8% of max
        return v / 9;  // same as dividing by 900%
    else {
        uint32_t y = (((uint32_t)v + 10486) << 8) / (10486 + 0xFFFFUL);  // add 16% of max and compare
        // to get a useful result with integer division, we shift left in the expression above
        // and revert what we've done again after squaring.
        y = y * y * y >> 8;
        if (y > 0xFFFFUL)  // prevent overflow
            return 0xFFFFU;
        else
            return (uint16_t)y;
    }
}