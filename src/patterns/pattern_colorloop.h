#pragma once

#include "../pattern.h"

class Pattern_Colorloop: public Pattern {
public:
    void loop();
    void init();
private:
    int col;
};
