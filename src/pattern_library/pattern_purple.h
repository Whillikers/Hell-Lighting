#pragma once

#include "../pattern_internals/pattern.h"

class Pattern_Purple: public Pattern {
public:
    void loop();
    void init();
private:
    int g;
};
