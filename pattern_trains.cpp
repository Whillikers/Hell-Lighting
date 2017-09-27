// Displays a number of points with tails//

#include "pattern_trains.h"

void Pattern_Trains::init() {
  clearLEDs();
  FastLED.setBrightness(BRIGHTNESS_MAX);

  // Randomly initialize speeds, colors, and positions //
  for (int i = 0; i < NUM_TRAINS; i++) {
    Train* train = trains + i;
    train->pos = random(0, NUM_LEDS_TOTAL);
    train->speed = random(1, MAX_SPEED);
    if (random(0, 2)) train-> speed *= -1;
    train->hue = random(0, 256);
    train->acceleration = 0;
  }
  cycle = ACCELERATION_CYCLE;
}

void Pattern_Trains::loop() {
  for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
    leds[i] = CRGB::Black;
  }

  // Update positions and colors //
  for (int i = 0; i < NUM_TRAINS; i++) {
    if (i > map(analogRead(PIN_POT), 0, POT_MAX, 0, NUM_TRAINS)) break; // Dial selects how many trains are visible and updates

    Train* train = trains + i;
    train->pos = (train->pos + train->speed + NUM_LEDS_TOTAL) % NUM_LEDS_TOTAL;

    leds[transform(train->pos)] = CHSV(train->hue, 255, 255);
    int trainLength = train->speed * TRAIL_LENGTH;
    for (int j = train->pos; j != train->pos - trainLength; j--) {
      CRGB newCol = CHSV(train->hue, 255, map(j - train->pos, 0, trainLength, 0, 255));
      leds[transform(j)].r += newCol.r;
      leds[transform(j)].g += newCol.g;
      leds[transform(j)].b += newCol.b;
    }
  }

  // cycle--;
  // if (!cycle) {
  //   cycle = ACCELERATION_CYCLE;
  //   for (int i = 0; i < NUM_TRAINS; i++) {
  //     Train* train = trains + i;
  //     if (train->acceleration) {
  //       train->speed += train->acceleration;
  //       if (!train->speed) train->acceleration = 0;
  //     }
  //     else { //not accelerating
  //       if (!random(0, ACCELERATE_CHANCE)) { //start accelerating
  //         if (train->speed) train->acceleration = train->speed > 0 ? -1 : 1; //not stopped
  //         else train->acceleration = random(0, 2) ? -1 : 1; //stopped
  //       }
  //     }
  //   }
  // }

  FastLED.show();
  delay(10);
}
