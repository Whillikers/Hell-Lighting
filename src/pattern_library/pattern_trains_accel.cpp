// Displays a number of points with tails//

#include "pattern_trains_accel.h"

int signum_accel(int input) {
  if (input > 0) return 1;
  if (input < 0) return -1;
  return 0;
}

int Pattern_Trains_Accel::targetTail(Train_Accel *train) {
  return train->speed * TRAIL_LENGTH;
}

void Pattern_Trains_Accel::init() {
  clearLEDs();
  FastLED.setBrightness(BRIGHTNESS_MAX);

  // Randomly initialize speeds, colors, and positions //
  for (int i = 0; i < NUM_TRAINS; i++) {
    Train_Accel* train = trains + i;
    train->pos = random(0, NUM_LEDS_TOTAL);
    train->speed = random(1, MAX_SPEED);
    if (random(0, 2)) train->speed *= -1;
    train->topSpeed = train->speed;
    train->tail = targetTail(train);
    train->hue = random(0, 256);
    train->acceleration = 0;
  }
  cycle = ACCELERATION_CYCLE;
}

void Pattern_Trains_Accel::loop() {
  for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
    leds[i] = CRGB::Black;
  }

  // Update positions and colors //
  for (int i = 0; i < NUM_TRAINS; i++) {
    if (i > map(board.getPotentiometer(0).getAngle8(), 0, MAX_8BIT, 0, NUM_TRAINS)) break; // Dial selects how many trains are visible and updates

    Train_Accel* train = trains + i;
    train->pos = (train->pos + train->speed + NUM_LEDS_TOTAL) % NUM_LEDS_TOTAL;

    leds[transform(train->pos)] = CHSV(train->hue, 255, 255);
    train->tail += signum_accel(targetTail(train) - train->tail);
    int tailSign = -signum_accel(train->tail);
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

    cycle--;
    if (!cycle) {
      cycle = ACCELERATION_CYCLE;
      for (int i = 0; i < NUM_TRAINS; i++) {
        Train_Accel* train = trains + i;
        if (train->acceleration) {
          train->speed += train->acceleration;
          if (!train->speed || train->speed == train->topSpeed) train->acceleration = 0;
        }
        else { //not accelerating
          int chance = train->speed ? DECELERATE_CHANCE : ACCELERATE_CHANCE;
          if (!random(0, chance)) { //begin acceleration/deceleration
            int speedSign = signum_accel(train->topSpeed);
            if (train->speed) train->acceleration = -speedSign; //not stopped
            else train->acceleration = speedSign; //stopped
          }
        }
      }
    }

  FastLED.show();
  delay(10);
}
