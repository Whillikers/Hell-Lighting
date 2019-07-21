#include "pattern_cssort.h"

#define SORT_ARR_SIZE NUM_LEDS_TOTAL
// TODO actually only want NUM_LEDS_TOTAL/255 ?
// like each element spans multiple LEDs
// can even blink outer LEDs in each bit to indicate accesses/swaps


void Pattern_CSSorting::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);

    // initialize arr to [0 ... SORT_ARR_SIZE - 1]
    arr = new int[SORT_ARR_SIZE];
    for (int i = 0; i < SORT_ARR_SIZE; i++) {
        arr[i] = i;
    }
    srand(millis());
    shuffleArr();

    state = up;
    current = 0;
    lowIdx = 0;
    highIdx = SORT_ARR_SIZE - 2;
    swapOccurred = false;

    for (int k = 0; k < NUM_LEDS_TOTAL; k++) {
        leds[transform(k)] = CHSV(map(arr[k], 0, NUM_LEDS_TOTAL, 0, 255), 255, 255);
    }
    FastLED.show();
    delay(1000); // wait a second before we start
}

void Pattern_CSSorting::cleanup() {
    delete[] arr;
}

bool Pattern_CSSorting::isFinished() {
    return (state == finished);
}

void Pattern_CSSorting::loop() {
    // find the next potential swap (or hit an end of the array)
    switch (state) {
    case up:
        while (current < highIdx && arr[current] <= arr[current + 1]) {
            current++;
        }
        break;
    case down:
        while (current > lowIdx && arr[current] <= arr[current + 1]) {
            current--;
        }
        break;
    default:
        break;
    }

    // make swap if applicable
    if (arr[current] > arr[current + 1]) {
        int right = arr[current + 1];
        arr[current + 1] = arr[current];
        arr[current] = right;

        swapOccurred = true;
        lastSwap = current;

        updateLEDs(current);
        updateLEDs(current + 1);
        FastLED.show();
    }

    // check for state change (when hitting end)
    if (current == lowIdx || current == highIdx) {
        if (swapOccurred) {
            swapOccurred = false;
            current = lastSwap;
            if (state == up) {
                state = down;
                highIdx = lastSwap;
            } else {
                state = up;
                current = lastSwap;
                lowIdx = lastSwap;
            }
        } else {
            delay(1000); // give time to enjoy sorted LEDs
            state = finished;
        }
    }

#ifdef SORT_STEP_DELAY
    delay(SORT_STEP_DELAY);
#endif
}

void Pattern_CSSorting::updateLEDs(int i) {
    leds[transform(i)] = CHSV(map(arr[i], 0, SORT_ARR_SIZE, 0, 255), 255, 255);
}

void Pattern_CSSorting::shuffleArr() {
    for (int i = 0; i < SORT_ARR_SIZE; i++) {
        int j = i + rand() % (SORT_ARR_SIZE - i);

        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}
