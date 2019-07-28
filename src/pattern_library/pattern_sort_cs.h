#pragma once

#include "../pattern_internals/sorter_pattern.h"

class Pattern_CSSorting: public SorterPattern {
protected:
    void sorterInit() override;
    void sorterLoop() override;

    unsigned int getElementWidth() override;

private:
    enum SorterState { UP, DOWN };
    SorterState state;

    int lowIdx;
    int highIdx;
    int current;

    bool swapOccurred;
    int lastSwap;
};
