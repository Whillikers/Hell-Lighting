#include "pattern_red_dot.h"

/*
 * This pattern sends a small red pulse traveling around in a circle.
 * Has persistence of vision effects at higher speeds.
 *
 * POT -> change dot speed.
 */

void Pattern_Red_Dot::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);
}

void Pattern_Red_Dot::loop() {
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      leds[transform(i)] = CRGB::Red;
      leds[transform(i + 1)] = CRGB::Red;
      leds[transform(i - 1)] = CRGB::Black;
      FastLED.show();
      delay(map(analogRead(PIN_POT), 0, POT_MAX, 1, 120));
    }
}
