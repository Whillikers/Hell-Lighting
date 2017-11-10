#include "pattern_colorloop.h"

void Pattern_Colorloop::init() {   
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);
    col = 0;
}

void Pattern_Colorloop::loop() {
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      leds[transform(i)] = CHSV(col, 255, 255);
    }

    col += map(analogRead(PIN_POT), POT_MAX, 0, 1, 10);
    if (col >= 255) col -= 255;
    FastLED.show();
    delay(10);
}
