#pragma once

#include "pattern.h"

typedef struct {
    int pos;
    int speed;
    int hue;
    int acceleration;
} Train;

class Pattern_Trains: Pattern {
public:
    void loop();
    void init();
private:
    const static int NUM_TRAINS = 12;
    const static int TRAIL_LENGTH = 10;
    const static int MAX_SPEED = 10;
    const static int ACCELERATION_CYCLE = 10; //number of loop cycles to wait to update speed
    const static int ACCELERATE_CHANCE = 5; //1 / (chance that a train will begin to accelerate/decelerate)

    Train trains[NUM_TRAINS];
    int cycle; //index in the acceleration cycle (counts down to 0)
};
