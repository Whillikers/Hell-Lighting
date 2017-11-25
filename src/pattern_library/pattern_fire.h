#pragma once

#include "../pattern_internals/pattern.h"

class Pattern_Fire: public Pattern {
public:
    void loop();
    void init();
private:
    int x;
};
