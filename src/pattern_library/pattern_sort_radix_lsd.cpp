#include "pattern_sort_radix_lsd.h"

void Pattern_SortingRadixLSD::sorterInit() {
    arrCopy = new uint8_t[getArrSize()];
    currentBase = 0;
    prepNewBase();
}
void Pattern_SortingRadixLSD::sorterLoop() {
    if (currentlyBucketing == getArrSize()) {
        currentBase++;
        if (getArrSize() >> currentBase) {
            prepNewBase();
        } else {
            signalDoneSorting();
        }
    }
    int currentBaseMask = (1 << currentBase);

    if ( arrCopy[currentlyBucketing] & currentBaseMask ) {
        arrSet(rightBucketCurrent++, arrCopy[currentlyBucketing]);
    } else {
        arrSet(leftBucketCurrent++, arrCopy[currentlyBucketing]);
    }
    currentlyBucketing++;
}
void Pattern_SortingRadixLSD::sorterCleanup() {
    delete[] arrCopy;
}

void Pattern_SortingRadixLSD::prepNewBase() {
    int currentBaseMask = (1 << currentBase);

    leftBucketCurrent = 0;
    rightBucketCurrent = 0;
    for (int i = 0; i < getArrSize(); i++) {
        if ( ~ arrGet(i) & currentBaseMask ) {
            rightBucketCurrent++;
        }
        arrCopy[i] = arrGet(i);
    }
    // TODO better implementation of buckets with linked lists or something
    // instead of this inefficient second pass

    currentlyBucketing = 0;
}
