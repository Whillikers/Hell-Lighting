#include "pattern_purple.h"

void Pattern_Purple::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);
    g = 0;
}

void Pattern_Purple::loop() {
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      leds[transform(i)] = ((i + g) % 3 == 0) ? CRGB::Purple : CRGB::Black;
    }

    FastLED.show();
    g = (g + 1) % 3;
    delay(map(board.getPotentiometer(0).getAngle8(), 0, MAX_8BIT, 1, 150));
}
