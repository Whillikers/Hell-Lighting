#include "sorter_pattern.h"

void SorterPattern::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);

    marked = new bool[getArrSize()];
    // initialize arr to [0 ... getArrSize() - 1]
    arr = new uint8_t[getArrSize()];
    for (int i = 0; i < getArrSize(); i++) {
        arr[i] = i;
        marked[i] = false;
        updateLEDs(i);
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
        if (t >= getStartDelay()) {
            state = SORT;
        }
        break;
    case SORT:
        sorterLoop();
        for (int i = 0; i < getArrSize(); i++) {
            updateLEDs(i);
        }
        FastLED.show();
        break;
    case POST_SORT:
        if (t >= getEndDelay()) {
            state = FINISHED;
        } else if ( (t / 1000) & 1 ) {
            if (!blinkState) {
                blinkOn();
                blinkState = true;
            }
        } else {
            if (blinkState) {
                clearLEDs();
                blinkState = false;
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

void SorterPattern::mark(int i) {
    marked[i] = true;
}


void SorterPattern::sorterInit() {}
void SorterPattern::sorterLoop() {}
void SorterPattern::sorterCleanup() {}

void SorterPattern::signalDoneSorting() {
    state = POST_SORT;
    blinkState = false;
    lastEvent = millis();
}

uint8_t SorterPattern::arrGet(int i) {
    if (getMarkAccess()) {
        mark(i);
    }
    return arr[i];
}
void SorterPattern::arrSet(int i, uint8_t val) {
    if (getMarkEdits()) {
        mark(i);
    }
    arr[i] = val;
}
void SorterPattern::arrSwap(int i, int j) {
    if (getMarkAccess() || getMarkEdits()) {
        mark(i);
        mark(j);
    }

    if (i != j) {
        uint8_t tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}
void SorterPattern::arrShuffle() {
    for (int i = 0; i < getArrSize(); i++) {
        int j = i + rand() % (getArrSize() - i);
        arrSwap(i, j);
    }
}

void SorterPattern::updateLEDs(int i) {
    CHSV color(map(arr[i], 0, getArrSize(), 0, 255), 255, 255);
    int elemStart = getElementWidth() * i;
    int k = 0;

    // first getMarkWidth() LEDs depend on marked[i]
    if (marked[i]) {
        for (; k < getMarkWidth(); k++) {
            leds[transform(elemStart + k)] = CRGB::Black;
        }
        marked[i] = false;
    } else {
        for (; k < getMarkWidth(); k++) {
            leds[transform(elemStart + k)] = color;
        }
    }

    // remaining LEDS only depend on color
    for (; k < getElementWidth(); k++) {
        leds[transform(elemStart + k)] = color;
    }
}

void SorterPattern::blinkOn() {
    for (int i = 0; i < getArrSize(); i++) {
        marked[i] = false;
        updateLEDs(i);
    }
    FastLED.show();
}
