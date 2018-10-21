#include "pattern_marbling.h"

void Pattern_Marbling::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);
}

void Pattern_Marbling::loop() {
    hue = map(analogRead(PIN_POT), 0, POT_MAX, 0, 255);

    for (int i = 0; i < NUM_LEDS_TOTAL / led_groups; i++) {
        int b = random(0, brightness_levels);
        int brightness = b * brightness_step + min_brightness;
        leds[i * led_groups + group] = CHSV(hue, 255, brightness);
    }

    group++;
    if (group >= led_groups) {
        group = 0;
    }

    FastLED.show();
}
