#include "sorter_pattern.h"

void SorterPattern::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);

    // initialize arr to [0 ... SORT_ARR_SIZE - 1]
    arr = new int[SORT_ARR_SIZE];
    for (int i = 0; i < SORT_ARR_SIZE; i++) {
        arr[i] = i;
    }
    srand(millis());
    arrShuffle();

    FastLED.show();

    state = PRE_SORT;
    lastEvent = millis();

    sorterInit();
}

void SorterPattern::loop() {
    unsigned long t = millis() - lastEvent;
    switch(state) {
    case PRE_SORT:
        if (t > START_DELAY) {
            state = SORT;
        }
        break;
    case SORT:
        sorterLoop();
        FastLED.show();
        break;
    case POST_SORT:
        if (t > END_DELAY) {
            state = FINISHED;
        } else if (blinkState != ((t / 1000) & 1 == 0)) {
            // true every other second
            blinkState = !blinkState;

            if (blinkState) {
                blinkOn();
            } else {
                blinkOff();
            }
        }
        break;
    default:
        break;
    }
}
void SorterPattern::cleanup() {
    sorterCleanup();
    delete[] arr;
}
bool SorterPattern::isFinished() {
    return (state == FINISHED);
}

void SorterPattern::sorterInit() {}
void SorterPattern::sorterLoop() {}
void SorterPattern::sorterCleanup() {}

void SorterPattern::signalDoneSorting() {
    state = POST_SORT;
    blinkState = false;
    lastEvent = millis();
}

int SorterPattern::arrGet(int i) {
    return arr[i];
}
void SorterPattern::arrSet(int i, int val) {
    arr[i] = val;
    updateLEDs(i);
}
void SorterPattern::arrSwap(int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
    updateLEDs(i);
    updateLEDs(j);
}
void SorterPattern::arrShuffle() {
    for (int i = 0; i < SORT_ARR_SIZE; i++) {
        int j = i + rand() % (SORT_ARR_SIZE - i);
        arrSwap(i, j);
    }
}

void SorterPattern::updateLEDs(int i) {
    CHSV color(map(arr[i], 0, SORT_ARR_SIZE, 0, 255), 255, 255);

    for (int k = WIDTH * i; k < WIDTH * (i + 1); k++) {
        leds[transform(k)] = color;
    }
}

void SorterPattern::blinkOff() {
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
        leds[i] = CRGB::Black;
    }
}
void SorterPattern::blinkOn() {
    for (int i = 0; i < SORT_ARR_SIZE; i++) {
        updateLEDs(i);
    }
}
