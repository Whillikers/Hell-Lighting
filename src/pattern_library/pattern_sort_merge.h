#pragma once

#include "../pattern_internals/sorter_pattern.h"

enum RequiredActionType {SPLIT, MERGE};

typedef struct RequiredAction_ {
    RequiredActionType type;
    unsigned int start;
    unsigned int mid;
    unsigned int end;
} RequiredAction;

typedef struct ListNode_ {
    RequiredAction* element;
    struct ListNode_* next;
} ListNode;

class PendingStack {
    public:
        PendingStack();
        ~PendingStack();

        void pushSplitAction(int start, int end);
        void pushMergeAction(int start, int mid, int end);

        RequiredAction* pop();
        unsigned int getSize();
        bool nonempty();
    private:
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
