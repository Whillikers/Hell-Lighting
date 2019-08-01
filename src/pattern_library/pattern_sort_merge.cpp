#include "pattern_sort_merge.h"

// PendingStack implementation

void PendingStack::pushSplitAction(int start, int end) {
    RequiredAction* action = new RequiredAction;
    action->type = SPLIT;
    action->start = start;
    action->end = end;
    push(action);
}
void PendingStack::pushMergeAction(int start, int mid, int end) {
    RequiredAction* action = new RequiredAction;
    action->type = MERGE;
    action->start = start;
    action->mid = mid;
    action->end = end;
    push(action);
}

// Pattern_MergeSort implementation

void Pattern_MergeSort::sorterInit() {
    actionsToDo.pushSplitAction(0, getArrSize());
    mergeInProgress = false;
}

void Pattern_MergeSort::prepNextMerge() {
    RequiredAction* pendingAction = actionsToDo.pop();

    while (pendingAction != NULL && pendingAction->type == SPLIT) {
        if (pendingAction->end - pendingAction->start > 1) {
            int mid = (pendingAction->start + pendingAction->end)/2;
            actionsToDo.pushMergeAction(pendingAction->start, mid, pendingAction->end);
            actionsToDo.pushSplitAction(pendingAction->start, mid);
            actionsToDo.pushSplitAction(mid, pendingAction->end);
        }
        delete pendingAction;
        pendingAction = actionsToDo.pop();
    }
    if (pendingAction == NULL) {
        signalDoneSorting();
        return;
        /*
         * This is an edge case: there is always a merge action at the
         * bottom of the stack (and thus this loop would eventually find a merge
         * action to perform) except at the beginning of the sort. Therefore, if
         * we encounter a stack of just a split action that does not trigger any
         * merge actions, the arr size was < 2 (and thus we're done sorting)
         */
    }

    mergeInProgress = true;

    mergeSize = pendingAction->end - pendingAction->start;
    mergeBuffer = new uint8_t[mergeSize];

    mergeSourceA = 0;
    mergeSourceB = pendingAction->mid - pendingAction->start;
    mergeBoundary = mergeSourceB;

    for (int i = 0; i < mergeSize; i++) {
        mergeBuffer[i] = arrGet(pendingAction->start + i);
        // copy two halves to merge into a buffer array
        // the merger will overwrite this region of arr
    }

    mergeDestination = pendingAction->start;

    delete pendingAction;
}

void Pattern_MergeSort::sorterLoop() {
    if (mergeInProgress) {
        if (mergeSourceA == mergeBoundary && mergeSourceB == mergeSize) {
            mergeInProgress = false;
            delete[] mergeBuffer;
        } else if (mergeSourceA == mergeBoundary) {
            arrSet(mergeDestination++, mergeBuffer[mergeSourceB++]);
        } else if (mergeSourceB == mergeSize) {
            arrSet(mergeDestination++, mergeBuffer[mergeSourceA++]);
        } else if (mergeBuffer[mergeSourceA] <= mergeBuffer[mergeSourceB]) {
            arrSet(mergeDestination++, mergeBuffer[mergeSourceA++]);
        } else {
            arrSet(mergeDestination++, mergeBuffer[mergeSourceB++]);
        }
    } else if (actionsToDo.nonempty()) {
        prepNextMerge();
    } else {
        signalDoneSorting();
    }
}

void Pattern_MergeSort::sorterCleanup() {
    if (mergeInProgress) {
        delete[] mergeBuffer;
    }
}
