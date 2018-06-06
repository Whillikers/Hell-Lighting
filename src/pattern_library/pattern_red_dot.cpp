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
      delay(map(board.getPotentiometer(0).getAngle8(), 0, MAX_8BIT, 1, 120));
    }
}
