#pragma once

#include "../pattern_internals/sorter_pattern.h"

// first, some helper classes/structs/enums for merge sort

// two types of action we may need to perform
enum RequiredActionType {SPLIT, MERGE};

// all information necessary to perform either of these actions
typedef struct RequiredAction_ {
    RequiredActionType type;
    unsigned int start;
    unsigned int mid;
    unsigned int end;
} RequiredAction;

/**
 * A data structure for keeping track of actions performed by Merge Sort
 * (analogous to the call stack in a normal recursive merge sort)
 */
class PendingStack {
    public:
        PendingStack();
        ~PendingStack();

        /**
         * Add a split action to the stack
         * @param start the start index of the split action
         * @param end   the end index of the split action
         */
        void pushSplitAction(int start, int end);
        /**
         * Add a merge action to the stack
         * @param start the start index of the merge action
         * @param mid   the middle index of the merge action
         * @param end   the end index of the merge action
         */
        void pushMergeAction(int start, int mid, int end);

        /**
         * Get the next required action
         * @return pointer to the action on top, or NULL if stack is empty
         */
        RequiredAction* pop();

        /**
         * Determine whether stack has any elements
         * @return true if stack has size >= 1, false if stack is empty
         */
        bool nonempty();
    private:
        typedef struct ListNode_ {
            RequiredAction* element;
            struct ListNode_* next;
        } ListNode;

        void push(RequiredAction* action);

        ListNode* top;
        unsigned int size;
};

class Pattern_MergeSort: public SorterPattern {
protected:
    void sorterInit() override;
    void sorterLoop() override;
    void sorterCleanup() override;

private:
    void prepNextMerge();

    PendingStack actionsToDo;

    bool mergeInProgress;
    unsigned int mergeSourceA;
    unsigned int mergeSourceB;
    unsigned int mergeBoundary;
    unsigned int mergeSize;
    unsigned int mergeDestination;

    uint8_t* mergeBuffer;
};
