#pragma once

#include "../pattern_internals/sorter_pattern.h"

class Pattern_CSSorting: public SorterPattern {
protected:
    void sorterInit();
    void sorterLoop();

    int WIDTH = 5;

private:
    enum SorterState { UP, DOWN };
    SorterState state;

    int lowIdx;
    int highIdx;
    int current;

    bool swapOccurred;
    int lastSwap;
};
