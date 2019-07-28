#include "pattern_sort_cs.h"

void Pattern_CSSorting::sorterInit() {
    state = UP;
    current = 0;
    lowIdx = 0;
    highIdx = getArrSize() - 2;
    swapOccurred = false;
}

void Pattern_CSSorting::sorterLoop() {
    // make swap if applicable
    if (arrGet(current) > arrGet(current + 1)) {
        arrSwap(current, current + 1);

        swapOccurred = true;
        lastSwap = current;
    }

    switch (state) {
    case UP:
        current++;
        break;
    case DOWN:
        current--;
        break;
    default:
        break;
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
                lowIdx = lastSwap;
            }
        } else {
            signalDoneSorting();
        }
    }
}
