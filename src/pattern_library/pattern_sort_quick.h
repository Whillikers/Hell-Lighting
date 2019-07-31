#pragma once

#include "../pattern_internals/sorter_pattern.h"

// first, some helper classes/structs/enums for merge sort

// all information necessary to perform either of these actions
typedef struct RequiredSort_ {
    unsigned int start;
    unsigned int end;
} RequiredSort;

/**
 * A queue for keeping track of actions performed by Quick Sort
 */
class PendingQueue {
    public:
        PendingQueue();
        ~PendingQueue();

        /**
         * Add a required sort to the queue
         * @param start the start index of the sort action
         * @param end   the end index of the sort action
         */
        void pushPendingSort(int start, int end);

        /**
         * Get the next required action
         * @return pointer to the action on top, or NULL if queue is empty
         */
        RequiredSort* pop();

        /**
         * Determine whether queue has any elements
         * @return true if queue has size >= 1, false if queue is empty
         */
        bool nonempty();
    private:
        typedef struct ListNode_ {
            RequiredSort* element;
            struct ListNode_* next;
        } ListNode;

        void push(RequiredSort* action);

        ListNode* front;
        ListNode* back;

        unsigned int size;
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
