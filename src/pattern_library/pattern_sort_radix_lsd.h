#pragma once

#include "../pattern_internals/sorter_pattern.h"

#define RADIX_LSD_ELEMENT_TYPE uint8_t
#define RADIX_LSD_ELEMENT_WIDTH 5
// 1226/5 = 245 < 256 (minimizing requires space for arrCopy)
// if more space is available, could also use type uint16_t and width 1

class Pattern_SortingRadixLSD: public SorterPattern {
protected:
    unsigned int getElementWidth() override;

    void sorterInit() override;
    void sorterCleanup() override;
    void sorterLoop() override;

private:
    RADIX_LSD_ELEMENT_TYPE* arrCopy;

    RADIX_LSD_ELEMENT_TYPE currentBase;
    RADIX_LSD_ELEMENT_TYPE leftBucketCurrent;
    RADIX_LSD_ELEMENT_TYPE rightBucketCurrent;
    RADIX_LSD_ELEMENT_TYPE currentlyBucketing;

    void prepNewBase();
};
