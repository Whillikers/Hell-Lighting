#pragma once

#include "../pattern.h"

#define BITS 100

class Pattern_Binary: public Pattern {
public:
    void loop();
    void init();
private:
    bool bits[BITS];
};
