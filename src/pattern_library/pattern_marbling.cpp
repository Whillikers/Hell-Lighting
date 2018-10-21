#include "pattern_marbling.h"

void Pattern_Marbling::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);
}

void Pattern_Marbling::loop() {
    hue = map(analogRead(PIN_POT), 0, POT_MAX, 0, 255);

    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
        int brightness = random(0, brightness_levels) * (255 / brightness_levels);
        leds[transform(i)] = CHSV(hue, 255, brightness);
    }

    FastLED.show();
}
