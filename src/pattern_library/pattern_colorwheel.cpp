#include "pattern_colorwheel.h"

void Pattern_Colorwheel::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);
    pos = 0;
}

void Pattern_Colorwheel::loop() {
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      leds[transform(i)] = CHSV(map(i + pos, 0, NUM_LEDS_TOTAL, 0, 255), 255, 255);
    }

    pos += map(board.getPotentiometer(0).getAngle8(), 0, MAX_8BIT, 0, 50);
    if (pos >= NUM_LEDS_TOTAL) pos -= NUM_LEDS_TOTAL;
    FastLED.show();
    delay(10);
}
