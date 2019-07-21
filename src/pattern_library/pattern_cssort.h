#pragma once

#include "../pattern_internals/pattern.h"

class Pattern_CSSorting: public Pattern {
public:
    void init();
    void cleanup();
    bool isFinished();

    void loop();

private:
    enum State { up, down, finished };
    State state;

    int lowIdx;
    int highIdx;
    int current;

    bool swapOccurred;
    int lastSwap;

    void shuffleArr();
    void updateLEDs(int idx);

    int* arr;
};
