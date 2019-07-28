#include "sorter_pattern.h"

unsigned int SorterPattern::getElementWidth() {
    return 1;
}
unsigned int SorterPattern::getArrSize() {
    return NUM_LEDS_TOTAL / getElementWidth();
}
unsigned int SorterPattern::getStartDelay() {
    return 2000;
}
unsigned int SorterPattern::getEndDelay() {
    return 7000;
}

void SorterPattern::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);

    // initialize arr to [0 ... getArrSize() - 1]
    arr = new int[getArrSize()];
    for (int i = 0; i < getArrSize(); i++) {
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
        if (t >= getStartDelay()) {
            state = SORT;
        }
        break;
    case SORT:
        sorterLoop();
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
                blinkOff();
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
    for (int i = 0; i < getArrSize(); i++) {
        int j = i + rand() % (getArrSize() - i);
        arrSwap(i, j);
    }
}

void SorterPattern::updateLEDs(int i) {
    CHSV color(map(arr[i], 0, getArrSize(), 0, 255), 255, 255);

    for (int k = getElementWidth() * i; k < getElementWidth() * (i + 1); k++) {
        leds[transform(k)] = color;
    }
}

void SorterPattern::blinkOff() {
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
        leds[i] = CRGB::Black;
    }
    FastLED.show();
}
void SorterPattern::blinkOn() {
    for (int i = 0; i < getArrSize(); i++) {
        updateLEDs(i);
    }
    FastLED.show();
}
