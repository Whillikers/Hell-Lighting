#include "pattern_sort_quick.h"

// PendingQueue implementation

void PendingQueue::pushPendingSort(int start, int end) {
    RequiredSort* action = new RequiredSort;
    action->start = start;
    action->end = end;
    push(action);
}

// Pattern_QuickSort implementation

void Pattern_QuickSort::sorterInit() {
    toSort.pushPendingSort(0, getArrSize());
    sortInProgress = false;
}

void Pattern_QuickSort::sorterLoop() {
    if (sortInProgress) {
        if (sortLeftPtr >= sortRightPtr) {
            sortInProgress = false;
            if (sortRightPtr - sortStart > 1) {
                toSort.pushPendingSort(sortStart, sortRightPtr);
            }
            if (sortEnd - sortLeftPtr > 1) {
                toSort.pushPendingSort(sortLeftPtr, sortEnd);
            }
        } else {
            while (arrGet(sortLeftPtr) < sortPivot) {
                sortLeftPtr++;
            }
            while (arrGet(sortRightPtr) > sortPivot) {
                sortRightPtr--;
            }
            if (sortLeftPtr < sortRightPtr) {
                arrSwap(sortLeftPtr, sortRightPtr);
            }
        }
    } else if (toSort.nonempty()) {
        RequiredSort* pending = toSort.pop();

        sortInProgress = true;

        sortStart = pending->start;
        sortEnd = pending->end;
        sortPivot = arrGet((sortStart + sortEnd) / 2);
        sortLeftPtr = sortStart;
        sortRightPtr = sortEnd - 1;

        delete pending;
    } else {
        signalDoneSorting();
    }
}
