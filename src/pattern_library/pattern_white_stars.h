#pragma once

#include "../pattern_internals/pattern.h"

class Pattern_White_Stars: public Pattern {
public:
    void loop();
    void init();
private:
    const int scalenumber = 100;
    const int specialFrequency = 20000;
    static const int minLights = 1; // out of 1000
    static const int maxLights = 100; // out of 1000
    static const int fadeRate = 20;
    float potValue;
};
