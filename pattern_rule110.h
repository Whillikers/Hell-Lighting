#pragma once

#include "pattern.h"
#include "topology.h"

class Pattern_Rule110: Pattern {
public:
    void loop();
    void init();
private:
    bool cells[NUM_LEDS_TOTAL];
};
