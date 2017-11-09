#pragma once

#include "pattern.h"

class Pattern_Color: public Pattern {
public:
    void loop();
    void init();
private:
    CHSV col;
};
