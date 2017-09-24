#include "pattern_flicker.h"

void Pattern_Flicker::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX / 3);
    for (int i = 0; i < lights_per_side; i++) {
        countdowns_left[i] = random(0, map(analogRead(PIN_POT), 0, POT_MAX, 10, maxframes_wait));
        countdowns_right[i] = random(0, map(analogRead(PIN_POT), 0, POT_MAX, 10, maxframes_wait));
        durations_left[i] = 0;
        durations_right[i] = 0;
    }
}

void Pattern_Flicker::loop() {
    for (int i = 0; i < lights_per_side; i++) {
        // Left side
        if (durations_left[i] > 0) { // We are mid-flicker
            for (int j = 0; j < len_light; j++) {
                int index = LEFT_START + i * (len_gap + len_light) + j;
                leds[transform(index)] = CRGB::Black;
            }

            durations_left[i]--;
            if (durations_left[i] <= 0) {
                countdowns_left[i] = random(0, map(analogRead(PIN_POT), 0, POT_MAX, 10, maxframes_wait));
            }
        } else {
            // We are still counting down
            for (int j = 0; j < len_light; j++) {
                int index = LEFT_START + i * (len_gap + len_light) + j;
                leds[transform(index)] = CRGB(255, 197, 46);
            }
            countdowns_left[i]--;
            if (countdowns_left[i] <= 0) { // Begin a flicker
                durations_left[i] = random(0, maxframes_flicker);
            }
        }

        // Right side
        if (durations_right[i] > 0) { // We are mid-flicker
            for (int j = 0; j < len_light; j++) {
                int index = RIGHT_END + i * (len_gap + len_light) + j;
                leds[transform(index)] = CRGB::Black;
            }

            durations_right[i]--;
            if (durations_right[i] <= 0) {
                countdowns_right[i] = random(0, map(analogRead(PIN_POT), 0, POT_MAX, 10, maxframes_wait));
            }
        } else {
            // We are still counting down
            for (int j = 0; j < len_light; j++) {
                int index = RIGHT_END + i * (len_gap + len_light) + j;
                leds[transform(index)] = CRGB(255, 197, 46);
            }
            countdowns_right[i]--;
            if (countdowns_right[i] <= 0) { // Begin a flicker
                durations_right[i] = random(0, maxframes_flicker);
            }
        }
    }

    FastLED.show();
    delay(10);
}
