#pragma once

#include "pattern.h"

class Pattern_Binary: Pattern {
public:
    void loop();
    void init();
private:
    bool bits[1000];
    bool carry[1000];
};
