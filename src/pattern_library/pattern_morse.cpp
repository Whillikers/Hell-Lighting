/*
Displays a string in morse code. Pot determines speed.
*/

#include "pattern_morse.h"

void Pattern_Morse::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);

    int len = msgAscii.length();
    for (int i = 0; i < len; i++) {
        char ch = msgAscii[i];

        String m = "";
        if ('A' <= ch && ch <= 'Z') {
            m = morseLetters[ch - 'A'];
        } else if ('0' <= ch && ch <= '9') {
            m = morseNumbers[ch - '0'];
        } else if (ch == ' ') {
            m = " ";
        } else if (ch == ',') {
            m = "--..--";
        }

        msgMorse += m + " ";
    }

    msgLength = msgMorse.length();

    for (int i = 0; i < msgLength; i++) {
        char ch = msgMorse[i];

        if (ch == '-') {
            pixelLength += dashLength;
            for (int j = 0; j < dashLength; j++) {
                msgPixels += "1";
            }
        } else if (ch == '.') {
            pixelLength += dotLength;
            for (int j = 0; j < dotLength; j++) {
                msgPixels += "1";
            }
        } else if (ch == ' ') {
            pixelLength += space;
            for (int j = 0; j < space; j++) {
                msgPixels += "0";
            }
        }

        pixelLength += gap;
        for (int j = 0; j < gap; j++) {
            msgPixels += "0";
        }
    }

    // calculate how many copies of the message can be displayed
    repeats = NUM_LEDS_TOTAL / (pixelLength + minRepeatGap);
    int leftover = NUM_LEDS_TOTAL % (pixelLength + minRepeatGap);
    repeatGap += leftover / NUM_LEDS_TOTAL;
}

void Pattern_Morse::loop() {
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
        leds[transform(i)] = CRGB::Black;
    }

    lightIndex = msgStart;
    for (int i = 0; i < repeats; i++) {
        for (int j = 0; j < pixelLength; j++) {
            if (lightIndex >= NUM_LEDS_TOTAL) {
                lightIndex -= NUM_LEDS_TOTAL;
            }

            char ch = msgPixels[j];
            if (ch == '1') {
                leds[transform(lightIndex)] = CRGB::White;
            }

            lightIndex++;
        }

        lightIndex += repeatGap;
    }

    msgStart++;

    if (msgStart >= NUM_LEDS_TOTAL) {
        msgStart -= NUM_LEDS_TOTAL;
    }

    FastLED.show();

    delay(map(analogRead(PIN_POT), 0, POT_MAX, 1, 400));
}
