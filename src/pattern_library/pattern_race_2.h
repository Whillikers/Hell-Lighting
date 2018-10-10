#pragma once

#include "../pattern_internals/pattern.h"

class Pattern_Race_2: public Pattern {
public:
    void loop();
    void init();
private:
    enum State { countdown, race, finish };
    State state = countdown;
    int raceDist;
    static const int stp = 5;
    static const int shifts = 40;
    static const int maxSpeed = 5;
    static const int minSpeed = 2;
    float red, blue;
    int redSpeed, blueSpeed;
    int redSpeedLocations[shifts];
    int blueSpeedLocations[shifts];
    int redSpeeds[shifts];
    int blueSpeeds[shifts];

    static const int countdownFlashes = 3;
    static const int finishFlashes = 5;
    int flashcount = 0;
};
