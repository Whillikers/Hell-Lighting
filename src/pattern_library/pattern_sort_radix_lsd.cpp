#include "pattern_sort_radix_lsd.h"

void Pattern_SortingRadixLSD::sorterInit() {
    arrCopy = new uint8_t[getArrSize()];
    bucketStarts = new unsigned int[RADIX];

    shiftedRadix = 1;
    prepNewBase();
}
void Pattern_SortingRadixLSD::sorterLoop() {
    if (currentlyBucketing == getArrSize()) {
        shiftedRadix *= RADIX;
        if (shiftedRadix < getArrSize()) {
            prepNewBase();
        } else {
            signalDoneSorting();
            return;
        }
    }

    int bucket = arrCopy[currentlyBucketing] / shiftedRadix % RADIX;
    arrSet(bucketStarts[bucket]++, arrCopy[currentlyBucketing]);

    currentlyBucketing++;
}
void Pattern_SortingRadixLSD::sorterCleanup() {
    delete[] arrCopy;
    delete[] bucketStarts;
}

void Pattern_SortingRadixLSD::prepNewBase() {
    for (int r = 0; r < RADIX; r++) {
        bucketStarts[r] = 0;
    }

    for (int i = 0; i < getArrSize(); i++) {
        int bucket = arrGet(i) / shiftedRadix % RADIX;
        for (int j = bucket + 1; j < RADIX; j++) {
            bucketStarts[j]++;
        }
        // for every element in a given bucket, increment the starts of all greater buckets

        arrCopy[i] = arrGet(i);
    }

    currentlyBucketing = 0;
}
