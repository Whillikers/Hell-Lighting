/*
This is a night sky pattern that more or less randomly turns led's on and off.
everyonce and a while (ballpark 16 minutes) there will be a "special event"
that has the potential to turn on or off a very large number of LEDs.

pot -> used to determine the ratio of led's turned off to led's turned on.
*/

#include "pattern_white_stars.h"

void Pattern_White_Stars::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX / 2);
}

void Pattern_White_Stars::loop() {
    potValue = map(analogRead(PIN_POT), POT_MAX, 0, minLights, maxLights);

    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      if (leds[i].r != 0) { //Fade
        if (leds[i].r <= fadeRate) {
          leds[i] = CRGB::Black;
          continue;
        }

        leds[i].r -= fadeRate;
        leds[i].g -= fadeRate;
        leds[i].b -= fadeRate;
        continue;
      }

      int r = random(0, 10000);
      if (r < potValue) leds[i] = CRGB(150, 150, 150);
    }

    /*
    // delete some number of currently bright LEDs.
    for (int i = 0; i < random(potValue / scalenumber); i++){
      leds[random(NUM_LEDS_TOTAL)] = CRGB::Black;
    }

    // set some number of leds to be white.
    for (int i = 0; i < random((POT_MAX - potValue) / scalenumber); i++){
      leds[random(NUM_LEDS_TOTAL)] = CRGB::White;
    }
    */

    // periodically have a large increase or decrease in the number of lights.
    if (random(0, specialFrequency) == 0){
      for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
          int v = random(127, 256);
          leds[transform(i)] = CRGB(v, v, v);
      }
    }
    FastLED.show();
    delay(1);
}
