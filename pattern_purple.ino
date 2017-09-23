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
    delay(map(analogRead(PIN_POT), 0, POT_MAX, 1, 150));
}
