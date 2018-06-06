#include "pattern_color.h"

void Pattern_Color::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);
}

void Pattern_Color::loop() {
    col = CHSV(map(board.getPotentiometer(0).getAngle16(), 0, MAX_16BIT, 0, 255),
               255, 255);
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
        leds[transform(i)] = col;
    }

    FastLED.show();
}
