#include "pattern_sort_cs.h"

void Pattern_CSSorting::sorterInit() {
    state = UP;
    current = 0;
    lowIdx = 0;
    highIdx = SORT_ARR_SIZE - 2;
    swapOccurred = false;
}

void Pattern_CSSorting::sorterLoop() {
    // find the next potential swap (or hit an end of the array)
    switch (state) {
    case UP:
        while (current < highIdx && arrGet(current) <= arrGet(current + 1)) {
            current++;
        }
        break;
    case DOWN:
        while (current > lowIdx && arrGet(current) <= arrGet(current + 1)) {
            current--;
        }
        break;
    default:
        break;
    }

    // make swap if applicable
    if (arrGet(current) > arrGet(current + 1)) {
        arrSwap(current, current + 1);

        swapOccurred = true;
        lastSwap = current;
    }

    // check for state change (when hitting end)
    if (current == lowIdx || current == highIdx) {
        if (swapOccurred) {
            swapOccurred = false;
            current = lastSwap;
            if (state == UP) {
                state = DOWN;
                highIdx = lastSwap;
            } else {
                state = UP;
                current = lastSwap;
                lowIdx = lastSwap;
            }
        } else {
            signalDoneSorting();
        }
    }
}
