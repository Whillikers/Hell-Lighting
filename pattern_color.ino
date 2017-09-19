#include "pattern_color.h"

void Pattern_Color::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);
}

void Pattern_Color::loop() {  
    col = CHSV(map(analogRead(PIN_POT), 0, POT_MAX, 0, 255), 255, 255);
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
        leds[transform(i)] = col;
    }

    FastLED.show();
    delay(10);
}
