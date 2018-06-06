#pragma once

#include "../pattern_internals/pattern.h"

class Pattern_White_Stars: public Pattern {
public:
    void loop();
    void init();
private:
    const int scalenumber = 100;
    const int specialFrequency = 20000;
    uint16_t potValue;
};
