#include "pattern_fire.h"

void Pattern_Fire::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);
}

void Pattern_Fire::loop() {
    uint16_t brightness = max((float) BRIGHTNESS_MAX * (((float) (1024 - analogRead(PIN_POT))) / 1024.0), 5);
    FastLED.setBrightness(brightness);
    for (int i = 1; i < NUM_LEDS_TOTAL - 1; i++) {
      if (leds[i].r == 0) { // This point has not yet been initialized
        leds[i] = CRGB(random8(100, 255), random8(0, 50), 0);
      } else { // Standard fire algorithm
        x = ((leds[i-1].r - leds[i].r) - (leds[i + 1].r - leds[i].r)) / 4;
        leds[i].r = x + random8(100, 255);
        leds[i].g = random8(0, 20);
        leds[i].b = 0;
      }
    }

    FastLED.show();
    delay(31);
}
