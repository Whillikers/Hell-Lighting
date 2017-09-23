/*
 * This pattern starts with the LEDs all one color and then slowly changes the
 * color of n random LEDs, where n is determined by the input pot. A set of
 * three small random numbers is generated which are then applied to the
 * selected LEDs RGB channels. In theory the color of the entire setup should
 * drift slowly over time without there ever being recognizable transitions.
*/

#include "pattern_drift.h"

#define START_RED 128
#define START_GREEN 128
#define START_BLUE 128

#define MAX_RED_CHANGE 20
#define MAX_GREEN_CHANGE 20
#define MAX_BLUE_CHANGE 20

void Pattern_Drift::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);

    for(int i = 0; i < NUM_LEDS_TOTAL; i++){
        leds[i].red = START_RED;
        leds[i].blue = START_BLUE;
        leds[i].green = START_GREEN;
    }
    FastLED.show(); // this pushes the pattern to the LEDs
}

void Pattern_Drift::loop() {
    num = random(map(analogRead(PIN_POT), 0, 255, 0, NUM_LEDS_TOTAL));
    addSub = positiveNegative[random(1)];  // If this round adds or subtracts

    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      int color_change[] = { random(MAX_RED_CHANGE), random(MAX_GREEN_CHANGE), random(MAX_BLUE_CHANGE) };

      if (random(NUM_LEDS_TOTAL) < num) {
        for (int n = 0; n < 3; n++) {
          if (leds[i][n] < abs(color_change[n])) {
            leds[i][n] += color_change[n];
          } else {
            leds[i][n] += addSub * color_change[n];
          }
        }
      }
    }

    FastLED.show(); // this pushes the pattern to the LEDs
}
