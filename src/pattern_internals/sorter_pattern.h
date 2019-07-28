/**
 * @file sorter_pattern.h
 *
 * Intermediate superclass for patterns that depict sorting algorithms.
 * This effectively allows patterns to sort an array given functions that
 * get and set, given indices in the array to sort.
 *
 * Defines the Pattern superclass used for making every sorting patterns.
 */

#pragma once

#include "pattern.h"

/**
 * A superclass and framework for user-created patterns that visualize
 * sorting an array as sorting a color wheel.
 *
 * Patterns are written by extending SorterPattern (or one of its abstract subclasses)
 * and filling in the methods, which are called by the system backend.
 */
class SorterPattern: public Pattern {
public:
    void init();
    void loop();
    void cleanup();
    bool isFinished();

protected:
    virtual void sorterInit();
    virtual void sorterLoop();
    virtual void sorterCleanup();

    virtual unsigned int getElementWidth();
    virtual unsigned int getArrSize();
    virtual unsigned int getStartDelay();
    virtual unsigned int getEndDelay();

    // TODO customize whether/how swaps/accesses get highlighted by overriding

    void signalDoneSorting();
    uint16_t arrGet(int i);
    void arrSet(int i, uint16_t val);
    void arrSwap(int i, int j);
    void arrShuffle();

private:
    uint16_t* arr;

    enum PatternState { PRE_SORT, SORT, POST_SORT, FINISHED };
    PatternState state;
    unsigned long lastEvent;

    void updateLEDs(int i);
    void blinkOff();
    void blinkOn();
    bool blinkState;
};
