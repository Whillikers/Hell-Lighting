#pragma once

#include "pattern.h"

class Pattern_red_255: public Pattern {
public:
    void loop();
    void init();
private:
    void make_red();
    void make_false();
    bool is_random[NUM_LEDS_TOTAL];
};
