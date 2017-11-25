#include "pattern_colorloop_sin.h"

void Pattern_Colorloop_Sin::init() {   
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);
    start = 0;
}

void Pattern_Colorloop_Sin::loop() {
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      leds[transform(i)] = CHSV((map(i, 0, NUM_LEDS_TOTAL, 0, 255) + start), 255, sin8((i + start)));
    }
    FastLED.show();
    start += map(analogRead(PIN_POT), POT_MAX, 0, 0, 40);
    delay(10);
}
