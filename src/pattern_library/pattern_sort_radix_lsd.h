#pragma once

#include "../pattern_internals/sorter_pattern.h"

// 1226/5 = 245 < 256 (minimizing requires space for arrCopy)
// if more space is available, could also use type uint16_t and width 1

class Pattern_SortingRadixLSD: public SorterPattern {
protected:
    void sorterInit() override;
    void sorterCleanup() override;
    void sorterLoop() override;

private:
    uint8_t* arrCopy;

    uint8_t currentBase;
    uint8_t leftBucketCurrent;
    uint8_t rightBucketCurrent;
    uint8_t currentlyBucketing;

    void prepNewBase();
};
