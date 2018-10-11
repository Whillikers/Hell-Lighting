/*
Displays a string in morse code. Pot determines speed.
*/

#include "pattern_morse.h"

void Pattern_Morse::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);

    int len = strlen(msgAscii);
    for (int i = 0; i < len; i++) {
        char ch = msgAscii[i];

        char* m;
        if ('A' <= ch && ch <= 'Z') {
            m = morseLetters[ch - 'A'];
        } else if ('0' <= ch && ch <= '9') {
            m = morseNumbers[ch - '0'];
        } else if (ch == ' ') {
            m = " ";
        } else if (ch == ',') {
            m = "--..--";
        }

        strcat(msgMorse, m);
    }

    msgLength = strlen(msgMorse);

    for (int i = 0; i < msgLength; i++) {
        char ch = msgMorse[i];

        if (ch == '-') {
            pixelLength += dashLength;
        } else if (ch == '.') {
            pixelLength += dotLength;
        } else if (ch == ' ') {
            pixelLength += space;
        }

        pixelLength += gap;
    }
}

void Pattern_Morse::loop() {
}
