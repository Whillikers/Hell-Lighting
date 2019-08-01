#pragma once

#include "../pattern_internals/sorter_pattern.h"

class Pattern_CocktailShakerSort: public SorterPattern {
protected:
    unsigned int getElementWidth() override;
    void sorterInit() override;
    void sorterLoop() override;

private:
    enum SorterState { UP, DOWN };
    SorterState state;

    int lowIdx;
    int highIdx;
    int current;

    bool swapOccurred;
    int lastSwap;
};
