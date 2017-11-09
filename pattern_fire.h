#pragma once

#include "pattern.h"

class Pattern_Fire: public Pattern {
public:
    void loop();
    void init();
private:
    int x;
};
