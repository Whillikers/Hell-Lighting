#pragma once

#include "../pattern_internals/pattern.h"

class Pattern_Colorwheel: public Pattern {
public:
    void loop();
    void init();
private:
    int pos;
};
