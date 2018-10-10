#pragma once

#include "../pattern_internals/pattern.h"

class Pattern_Morse: public Pattern {
public:
    void loop();
    void init();
private:
    const int dashLength = 3;
    const int dotLength = 1;
    const int gap = 1;
    const int space = 3;

    int msgStart = 0;
    int msgLength = 0;
    int pixelLength = 0;

    char* msgAscii = "HELLO";
    char* msgMorse = "";
};

char* morseLetters[] = {
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

char* morseNumbers[] = {
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
