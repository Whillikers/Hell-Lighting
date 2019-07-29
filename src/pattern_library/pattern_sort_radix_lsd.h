#pragma once

#include "../pattern_internals/sorter_pattern.h"

class Pattern_SortingRadixLSD: public SorterPattern {
protected:
    void sorterInit() override;
    void sorterCleanup() override;
    void sorterLoop() override;

private:
    const unsigned int RADIX = 4;
    unsigned int shiftedRadix;

    uint8_t* arrCopy;
    unsigned int* bucketStarts;

    unsigned int currentlyBucketing;

    void prepNewBase();
};
