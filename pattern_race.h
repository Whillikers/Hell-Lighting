#pragma once

#include "pattern.h"

class Pattern_Race: public Pattern {
public:
    void loop();
    void init();
private:
    int s;
    static const int stp = 10;
    static const int shifts = 50;
    static const int maxSpeed = 10;
    float red, blue;
    int redSpeed, blueSpeed;
    int redSpeedLocations[shifts];
    int blueSpeedLocations[shifts];
    int redSpeeds[shifts];
    int blueSpeeds[shifts];
};
