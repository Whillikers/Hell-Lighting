#include "pattern_sort_quick.h"

// PendingQueue implementation

PendingQueue::PendingQueue() {
    front = NULL;
    back = NULL;
    size = 0;
}
PendingQueue::~PendingQueue() {
    while (size > 0) {
        delete front->element;
        pop();
    }
}

void PendingQueue::pushPendingSort(int start, int end) {
    RequiredSort* action = new RequiredSort;
    action->start = start;
    action->end = end;
    push(action);
}

RequiredSort* PendingQueue::pop() {
    if (size == 0) {
        return NULL;
    } else {
        RequiredSort* ret = front->element;
        ListNode* toDelete = front;
        front = front->next;
        delete toDelete;
        size--;
        return ret;
    }
}

bool PendingQueue::nonempty() {
    return size > 0;
}

void PendingQueue::push(RequiredSort* action) {
    ListNode* node = new ListNode;
    node->element = action;
    node->next = NULL;
    if (size == 0) {
        front = node;
        back = node;
    } else {
        back->next = node;
        back = node;
    }

    size++;
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
