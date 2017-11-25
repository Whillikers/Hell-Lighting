#pragma once

#include "../pattern_internals/pattern.h"

class Pattern_Rule110: public Pattern {
public:
    void loop();
    void init();
private:
    bool cells[NUM_LEDS_TOTAL];
};
