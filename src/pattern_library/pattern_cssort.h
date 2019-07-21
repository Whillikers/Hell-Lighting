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
    int i;
    bool swapOccurred;

    void shuffleArr();
    int* arr;
};
