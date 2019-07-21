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
    i = 0;
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
        while (i < SORT_ARR_SIZE - 2 && arr[i] <= arr[i + 1]) {
            i++;
        }
        break;
    case down:
        while (i > 0 && arr[i] <= arr[i + 1]) {
            i--;
        }
        break;
    default:
        break;
    }

    // make swap if applicable
    if (arr[i] > arr[i + 1]) {
        int right = arr[i + 1];
        arr[i + 1] = arr[i];
        arr[i] = right;
        swapOccurred = true;

        updateLEDs(i);
        updateLEDs(i + 1);
        FastLED.show();
    }

    // check for state change (when hitting end)
    if (i == 0 || i == NUM_LEDS_TOTAL - 2) {
        if (swapOccurred) {
            swapOccurred = false;
            state = (state == up) ? down : up;
        } else {
            state = finished;
        }
    }

#ifdef SORT_STEP_DELAY
    delay(SORT_STEP_DELAY);
#endif
}

void Pattern_CSSorting::updateLEDs(int idx) {
    leds[transform(i)] = CHSV(map(arr[idx], 0, SORT_ARR_SIZE, 0, 255), 255, 255);
}

void Pattern_CSSorting::shuffleArr() {
    for (int i = 0; i < SORT_ARR_SIZE; i++) {
        int j = i + rand() % (SORT_ARR_SIZE - i);

        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}
