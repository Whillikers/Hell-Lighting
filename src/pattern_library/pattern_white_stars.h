#pragma once

#include "../pattern_internals/pattern.h"

class Pattern_White_Stars: public Pattern {
public:
    void loop();
    void init();
private:
    const int scalenumber = 100;
    const int specialFrequency = 10000;
    static const int minLights = 1; // out of 1000
    static const int maxLights = 200; // out of 1000
    static const int fadeRate = 10;
    float potValue;
};
