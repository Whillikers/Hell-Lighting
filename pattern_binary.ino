/*
 * A pattern that counts in binary. TODO: Make more efficient.
 */

#include "pattern_binary.h"

void Pattern_Binary::init() {
    for (int i = 0; i < 1000; i++) {
        bits[i] = false;
        carry[i] = false;
    }
}

void Pattern_Binary::loop() {
    // Increment operation
    if (bits[0]) {
        bits[0] = false;
        carry[1] = true;
        leds[transform(0)] = CRGB::Black;
    } else {
        bits[0] = true;
        carry[1] = false;
        leds[transform(0)] = CRGB::Red;
    }

    // Ripple operation
    for (int i = 1; i < 999; i++) {
        if (bits[i] && carry[i]) {
            bits[i] = false;
            carry[i + 1] = true;
        } else if (bits[i] || carry[i]) {
            bits[i] = true;
            carry[i + 1] = false;
        } else {
            carry[i + 1] = false;
        }
    }

    // Apply colors (cached)
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
        if (i < LEFT_START || i > 800) {
            leds[transform(i)] = CRGB::Black;
            continue;
        }
        leds[transform(i)] = bits[i - LEFT_START] ? CRGB::Red : CRGB::Black;
    }

    FastLED.show();
    delay(1);
}
