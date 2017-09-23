#pragma once

#include "pattern.h"
//#include "topology.h" TODO: Find a way to include this

class Pattern_Rule110: Pattern {
public:
    void loop();
    void init();
private:
    bool cells[(332 + 285 + 355 + 254)];
};
