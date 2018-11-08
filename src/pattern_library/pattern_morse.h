#pragma once

#include "../pattern_internals/pattern.h"

class Pattern_Morse: public Pattern {
public:
    void loop();
    void init();
private:
    const int dashLength = 3;
    const int dotLength = 1;
    const int gap = 2;
    const int space = 3;
    const int minRepeatGap = 50;

    int msgStart = 0;
    int msgLength = 0;
    int pixelLength = 0;
    int lightIndex;

    int repeats;
    int repeatGap = minRepeatGap;

    String msgAscii = "GDBG";
    String msgMorse = "";
    String msgPixels = "";

    String morseLetters[26] = {
        ".-",
        "-...",
        "-.-.",
        "-..",
        ".",
        "..-.",
        "--.",
        "....",
        "..",
        ".---",
        "-.-",
        ".-..",
        "--",
        "-.",
        "---",
        ".--.",
        "--.-",
        ".-.",
        "...",
        "-",
        "..-",
        "...-",
        ".--",
        "-..-",
        "-.--",
        "--.."
    };

    String morseNumbers[10] = {
        "-----",
        ".----",
        "..---",
        "...--",
        "....-",
        ".....",
        "-....",
        "--...",
        "---..",
        "----.",
    };
};
