#include "pattern.h"

void pattern_race() {
  clearLEDs();
  FastLED.setBrightness(BRIGHTNESS_MAX);
  int s = min(abs(LEFT_END - LEFT_START), abs(RIGHT_END - RIGHT_START));
  const int stp = 10;
  const int shifts = 50;
  const int maxSpeed = 10;
  float red, blue;
  int redSpeed, blueSpeed;
  int redSpeedLocations[shifts];
  int blueSpeedLocations[shifts];
  int redSpeeds[shifts];
  int blueSpeeds[shifts];
  
  while (true) {
    // Initialize values //
    red = 0;
    blue = 0;
    redSpeed = random(1, maxSpeed);
    blueSpeed = random(1, maxSpeed);
    for (int i = 0; i < shifts; i++) {
      redSpeeds[i] = random(1, maxSpeed);
      blueSpeeds[i] = random(1, maxSpeed);
      redSpeedLocations[i] = random(0, 5 * s);
      blueSpeedLocations[i] = random(0, 5 * s);
    }

    // Flash countdown //
    for (int flashes = 0; flashes < 3; flashes++) {
      for (int i = LEFT_START; i < LEFT_END; i++) {
        leds[transform(i)] = CRGB::Red;
      }
      for (int i = RIGHT_START; i > RIGHT_END; i--) {
        leds[transform(i)] = CRGB::Blue;
      }
      FastLED.show();
      delay(500);
      for (int i = LEFT_START; i < LEFT_END; i++) {
        leds[transform(i)] = CRGB::Black;
      }
      for (int i = RIGHT_START; i > RIGHT_END; i--) {
        leds[transform(i)] = CRGB::Black;
      }
      FastLED.show();
      delay(500);
    }

    // Clear everything //
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      leds[i] = CRGB::Black;
    }

    // Run race //
    for (int i = 0; abs(red) < s && abs(blue) < s; i++) {
      // Update positions //
      red += ((float) redSpeed) / ((float) stp);
      blue += ((float) blueSpeed) / ((float) stp);

      for (int j = 0; j < shifts; j++) {
        if (redSpeedLocations[j] == i) redSpeed = redSpeeds[j];
        if (blueSpeedLocations[j] == i) blueSpeed = blueSpeeds[j];
      }
      
      leds[transform(LEFT_START + (int) red)] = CRGB::Red;
      leds[transform(RIGHT_START - (int) blue)] = CRGB::Blue;
      FastLED.show();
      delay(stp);
    }

    // Flash winner colors //
    for (int flashes = 0; flashes < 5; flashes++) {
      if (red > blue) {
        for (int i = LEFT_START; i < LEFT_END; i++) {
          leds[transform(i)] = CRGB::Red;
        }
        FastLED.show();
        delay(500);
        for (int i = LEFT_START; i < LEFT_END; i++) {
          leds[transform(i)] = CRGB::Black;
        }
        FastLED.show();
        delay(500);
      } else {
        for (int i = RIGHT_START; i > RIGHT_END; i--) {
          leds[transform(i)] = CRGB::Blue;
        }
        FastLED.show();
        delay(500);
        for (int i = RIGHT_START; i > RIGHT_END; i--) {
          leds[transform(i)] = CRGB::Black;
        }
        FastLED.show();
        delay(500);
      }
    }
  }
}
