#pragma once

#include "pattern.h"

class Pattern_GameOfLife: Pattern {
  public:
    void loop();
    void init();
  private:
    bool occupied[NUM_LEDS_TOTAL];
};