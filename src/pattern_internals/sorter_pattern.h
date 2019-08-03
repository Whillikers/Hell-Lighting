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
 * Essentially, a subclass may implement (and override) three functions:
 *  - sorterInit() to do any initialization of resources necessary for the algo
 *  - sorterLoop(), an operation to be performed repeatedly
 *  - sorterCleanup(), any deletes or operations necessary to exit cleanly
 *  These functions want to sort and array which can be accessed with arrGet()
 *  and modified with arrSet() and arrSwap(). When the sort is complete, call
 *  signalDoneSorting(). Once signalDoneSorting() is called, sorterLoop() will
 *  no longer be called.
 *
 * Sorting algorithms are visualized like so:
 *  - The LEDs are divided into elements, each of width 5
 *  - A random array of size (NUM_LEDS_TOTAL/width) is allocated and shuffled.
 *    It contains the integers [ 0 .. arr size - 1 ] in some random order.
 *  - This random array is displayed on the LEDs for 2000ms
 *  - Before this point, the sorter can
 *  - The sorting occurs. Each time loop() is called, sorterLoop() is called.
 *  - When the sorting is complete (as indicated by the subclass), all LEDs
 *    blink on and off for 7000ms
 *
 * Subclasses may override getElementWidth(), getArrSize(), getStartDelay(),
 * and getEndDelay() to modify parts of this behavior.
 */
class SorterPattern: public Pattern {
public:
    /**
     * Performs operations
     */
    void init();
    void loop();
    void cleanup();
    bool isFinished();

protected:
    /**
     * Called when init() is called, allows subclass to perform initialization
     */
    virtual void sorterInit();
    /**
     * Called when loop() is called when sorting is in progress. This is where
     * sorting operations should occurr
     */
    virtual void sorterLoop();
    /**
     * Called when cleanup() is called, allows subclass to perform any cleanup
     */
    virtual void sorterCleanup();

    /**
     * Determines the element width (default 5 unless overriden)
     * @return the width of each element, in number of LEDs
     */
    virtual unsigned int getElementWidth() { return 5; }
    /**
     * Determines the array size (default NUM_LEDS_TOTAL/width unless overriden)
     * @return the size of the array to be sorted
     */
    virtual unsigned int getArrSize() { return NUM_LEDS_TOTAL/getElementWidth(); }
    /**
     * Determines the time to wait before sorting begins (default 2000)
     * @return the start delay, in milliseconds
     */
    virtual unsigned int getStartDelay() { return 2000; }
    /**
     * Determines the time to wait after sorting ends (default 7000)
     * @return the end delay, in milliseconds
     */
    virtual unsigned int getEndDelay() { return 7000; }

    /** Determines whether to automatically "mark" edits to the array by
     * making the first markWidth() LEDs black for one loop
     */
    virtual bool getMarkEdits() { return true; }

    /** Determines whether to automatically "mark" accesses to the array by
     * making the first markWidth() LEDs black for one loop
     */
    virtual bool getMarkAccess() { return false; }

    /**
     * The width of the highlights for emphasizing accesses/edits.
     * CODE ASSUMES 0 <= markWidth() << getElementWidth()
     */
    virtual unsigned int getMarkWidth() { return 2; }

    /**
     * Indicate that the array is now sorted.
     */
    void signalDoneSorting();

    // functions for access the array
    uint8_t arrGet(int i);
    void arrSet(int i, uint8_t val);
    void arrSwap(int i, int j);
    void arrShuffle();

    /**
     * Manually mark one element of the array (regardless of whether
     * accesses/edits are automatically marked)
     * @param i the element to mark
     */
    void mark(int i);

private:
    uint8_t* arr;
    bool* marked;

    enum PatternState { PRE_SORT, SORT, POST_SORT, FINISHED };
    PatternState state;
    unsigned long lastEvent;

    void updateLEDs(int i);
    void blinkOn();
    bool blinkState;
};
