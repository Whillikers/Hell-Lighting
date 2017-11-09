#pragma once

#include "pattern.h"

class Pattern_Drift: public Pattern {
public:
    void loop();
    void init();
private:
    int num;
    int addSub;
    int positiveNegative[2] = {-1, 1};
};
