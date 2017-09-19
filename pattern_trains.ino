#include "pattern.h"

// Displays a number of points with tails//
void pattern_trains() {
  clearLEDs();
  FastLED.setBrightness(BRIGHTNESS_MAX);

  // Random number of trains //
  const int numTrains = 12;
  const int trailLength = 10;
  int trainPos[numTrains];
  int trainSpeeds[numTrains];
  int trainColors[numTrains];

  // Randomly initialize speeds, colors, and positions //
  for (int i = 0; i < numTrains; i++) {
    trainPos[i] = random(0, NUM_LEDS_TOTAL - 1);
    trainSpeeds[i] = random(-10, 10);
    if (trainSpeeds[i] == 0) trainSpeeds[i] = 1;
    trainColors[i] = random(0, 255);
  }
  
  while (true) {
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      leds[i] = CRGB::Black;
    }

    // Update positions and colors //
    for (int i = 0; i < numTrains; i++) {
      if (i > map(analogRead(PIN_POT), 0, POT_MAX, 0, numTrains)) break; // Dial selects how many trains are visible and updates
      
      trainPos[i] += trainSpeeds[i];
      
      if (trainPos[i] >= NUM_LEDS_TOTAL) trainPos[i] -= NUM_LEDS_TOTAL;
      if (trainPos[i] < 0) trainPos[i] += NUM_LEDS_TOTAL;
      
      leds[transform(trainPos[i])] = CHSV(trainColors[i], 255, 255);
      // Forward-moving trails //
      if (trainSpeeds[i] > 0) {
        for (int j = trainPos[i]; j > trainPos[i] - trainSpeeds[i] * trailLength; j--) {
          CRGB newCol = CHSV(trainColors[i], 255, map(j - trainPos[i], 0, trainSpeeds[i] * trailLength, 0, 255));
          leds[transform(j)].r += newCol.r;
          leds[transform(j)].g += newCol.g;
          leds[transform(j)].b += newCol.b;
        }

        continue;
      }
      
      // Backward-moving trails //
      for (int j = trainPos[i]; j < trainPos[i] - trainSpeeds[i] * trailLength; j++) {
          CRGB newCol = CHSV(trainColors[i], 255, map(j - trainPos[i], 0, trainSpeeds[i] * trailLength, 0, 255));
          leds[transform(j)].r += newCol.r;
          leds[transform(j)].g += newCol.g;
          leds[transform(j)].b += newCol.b;
        }
    }

    FastLED.show();
    delay(10);
  }
}
