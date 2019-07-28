#pragma once

#include "../pattern_internals/sorter_pattern.h"

class Pattern_SortingRadixLSD: public SorterPattern {
protected:
    void sorterInit() override;
    void sorterCleanup() override;
    void sorterLoop() override;

private:
    int* arrCopy;

    int currentBase;
    int leftBucketCurrent;
    int rightBucketCurrent;
    int currentlyBucketing;

    void prepNewBase();
};
