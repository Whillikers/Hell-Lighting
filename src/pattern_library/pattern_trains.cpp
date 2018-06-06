// Displays a number of points with tails//

#include "pattern_trains.h"

int signum(int input) {
  if (input > 0) return 1;
  if (input < 0) return -1;
  return 0;
}

int Pattern_Trains::targetTail(Train *train) {
  return train->speed * TRAIL_LENGTH;
}

void Pattern_Trains::init() {
  clearLEDs();
  FastLED.setBrightness(BRIGHTNESS_MAX);

  // Randomly initialize speeds, colors, and positions //
  for (int i = 0; i < NUM_TRAINS; i++) {
    Train* train = trains + i;
    train->pos = random(0, NUM_LEDS_TOTAL);
    train->speed = random(1, MAX_SPEED);
    if (random(0, 2)) train->speed *= -1;
    train->topSpeed = train->speed;
    train->tail = targetTail(train);
    train->hue = random(0, 256);
  }
}

void Pattern_Trains::loop() {
  for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
    leds[i] = CRGB::Black;
  }

  // Update positions and colors //
  for (int i = 0; i < NUM_TRAINS; i++) {
    if (i > map(board.getPotentiometer(0).getAngle8(), 0, MAX_8BIT, 0, NUM_TRAINS)) break; // Dial selects how many trains are visible and updates

    Train* train = trains + i;
    train->pos = (train->pos + train->speed + NUM_LEDS_TOTAL) % NUM_LEDS_TOTAL;

    leds[transform(train->pos)] = CHSV(train->hue, 255, 255);
    train->tail += signum(targetTail(train) - train->tail);
    int tailSign = -signum(train->tail);
    for (int j = train->pos; j != train->pos - train->tail; j += tailSign) {
      CRGB newCol = CHSV(train->hue, 255, map(j - train->pos, 0, train->tail, 0, 255));
      leds[transform(j)].r += newCol.r;
      leds[transform(j)].r /= 2;
      leds[transform(j)].g += newCol.g;
      leds[transform(j)].g /= 2;
      leds[transform(j)].b += newCol.b;
      leds[transform(j)].b /= 2;
    }
  }

  FastLED.show();
  delay(10);
}
