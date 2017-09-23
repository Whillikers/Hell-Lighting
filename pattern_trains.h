#pragma once

#include "pattern.h"

class Pattern_Trains: Pattern {
public:
    void loop();
    void init();
private:
    const static int numTrains = 12;
    const static int trailLength = 10;

    int trainPos[numTrains];
    int trainSpeeds[numTrains];
    int trainColors[numTrains];
};
