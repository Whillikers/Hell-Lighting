#pragma once

#include "pattern.h"

class Pattern_Colorloop: Pattern {
public:
    void loop();
    void init();
private:
    int col;
};
