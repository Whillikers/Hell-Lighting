// A Turing-complete pattern //
#include "pattern_rule110.h"

void Pattern_Rule110::init() {
    clearLEDs();
    // Initialize randomly
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
        if (random(0, 100) > 90) leds[i] = CRGB::White;
    }
    FastLED.setBrightness(BRIGHTNESS_MAX * 0.75);
}

void Pattern_Rule110::loop() {
    // Update cell data
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      if (leds[transform(i - 1)].r > 0) { // Left cell is lit
        if (leds[transform(i)].r > 0) { // Left and center cells are lit
          cells[i] = leds[transform(i + 1)].r == 0;
        } else { // Left cell is lit, center cell is not
          cells[i] = leds[transform(i + 1)].r > 0;
        }
      } else { // Left cell is unlit
        if (leds[transform(i)].r > 0) { // Left cell is unlit, center is lit
          cells[i] = true;
        } else { // Left cell is unlit, center is unlit
          cells[i] = leds[transform(i + 1)].r > 0;
        }
      }
    }

    // Update colors
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      if (cells[i]) leds[transform(i)] = CRGB::White;
      else leds[transform(i)] = CRGB::Black;
    }

    FastLED.show();
    delay(board.getPotentiometer(0).getAngle8() * 4 + 100);
}
