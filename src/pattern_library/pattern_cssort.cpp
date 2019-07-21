#include "pattern_cssort.h"

#define SORT_STEP_DELAY 10

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
}

void Pattern_CSSorting::cleanup() {
    delete[] arr;
}

bool Pattern_CSSorting::isFinished() {
    return (state == finished);
}

void Pattern_CSSorting::loop() {
    for (int k = 0; k < NUM_LEDS_TOTAL; k++) {
        leds[transform(k)] = CHSV(map(arr[k], 0, NUM_LEDS_TOTAL, 0, 255), 255, 255);
    }
    FastLED.show();

    int left = arr[i];
    int right = arr[i + 1];

    if (left > right) {
        swapOccurred = true;
        arr[i] = right;
        arr[i + 1] = left;
    }

    switch (state) {
    case up:
        i++;
        break;
    case down:
        i--;
        break;
    default:
        break;
    }

    if (i == NUM_LEDS_TOTAL - 1) {
        i = NUM_LEDS_TOTAL - 2;
        if (swapOccurred) {
            swapOccurred = false;
            state = down;
        } else {
            state = finished;
        }
    } else if (i < 0) {
        i = 0;
        if (swapOccurred) {
            state = up;
            swapOccurred = false;
        } else {
            state = finished;
        }
    }

    delay(SORT_STEP_DELAY);
}

void Pattern_CSSorting::shuffleArr() {
    for (int i = 0; i < SORT_ARR_SIZE; i++) {
        int j = i + rand() % (SORT_ARR_SIZE - i);

        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}
