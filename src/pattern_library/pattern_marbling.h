#pragma once

#include "../pattern_internals/pattern.h"

class Pattern_Marbling: public Pattern {
public:
    void loop();
    void init();
private:
    int hue;
    const int brightness_levels = 10;
};
