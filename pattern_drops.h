#pragma once

#include "pattern.h"

#define NUM_DROPS 5
#define MIN_DURATION 3000
#define MAX_DURATION 10000
#define MAX_SIZE (NUM_LEDS_TOTAL / 10)
#define DECAY 10.0

typedef struct {
  int center;
  CRGB color;
  bool receding;
  long start;
  long duration;
  double maxSize;
} Drop;

class Pattern_Drops: Pattern {
  public:
    void loop();
    void init();
  private:
    Drop drops[NUM_DROPS];
};