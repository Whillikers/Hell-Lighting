#pragma once

#include "../pattern_internals/sorter_pattern.h"
#include "../data_structures/queue.h"

// first, some helper classes/structs/enums for merge sort

// all information necessary to perform either of these actions
typedef struct RequiredSort_ {
    unsigned int start;
    unsigned int end;
} RequiredSort;

/**
 * A queue for keeping track of actions performed by Quick Sort
 */
class PendingQueue : public Queue<RequiredSort> {
    public:
        /**
         * Add a required sort to the queue
         * @param start the start index of the sort action
         * @param end   the end index of the sort action
         */
        void pushPendingSort(int start, int end);
};

class Pattern_QuickSort: public SorterPattern {
protected:
    void sorterInit() override;
    void sorterLoop() override;

private:
    bool sortInProgress;
    int sortStart, sortEnd;
    int sortPivot;
    int sortLeftPtr, sortRightPtr;

    PendingQueue toSort;
};
