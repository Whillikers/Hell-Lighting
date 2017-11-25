/*
 * A pattern that counts in binary.
 */

#include "pattern_binary.h"

void Pattern_Binary::init() {
    memset(&bits, 0, sizeof(bits));
    clearLEDs();
}

void Pattern_Binary::loop() {
    for (int i = 0; i < BITS; i++) {
        bits[i] = !bits[i];
        leds[transform(LEFT_START + i)] = bits[i] ? CRGB::Red : CRGB::Black;
        if (bits[i]) break; //no carry, so all other bits will stay the same
    }

    FastLED.show();
    delay(1);
}
