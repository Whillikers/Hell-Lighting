#pragma once

#include "../pattern_internals/pattern.h"

class Pattern_Colorloop_Sin: public Pattern {
public:
    void loop();
    void init();
private:
    int start;
};
