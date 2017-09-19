#include "pattern.h"

void pattern_fire() {
  int x;
  while (true) {
    uint16_t brightness = max((float) BRIGHTNESS_MAX * (((float) (1024 - analogRead(PIN_POT))) / 1024.0), 5);
    FastLED.setBrightness(brightness);
    for (int i = 1; i < NUM_LEDS_TOTAL - 1; i++) {
      if (leds[i].r == 0) { // This point has not yet been initialized
        leds[i] = CRGB(random(100, 255), random(0, 50), 0);
      } else { // Standard fire algorithm
        x = ((leds[i-1].r - leds[i].r) - (leds[i + 1].r - leds[i].r)) / 4;
        leds[i].r = x + random(100, 255);
        leds[i].g = random(0, 20);
        leds[i].b = 0;
      }
    }
  
    FastLED.show();
    delay(1);
  }
}
