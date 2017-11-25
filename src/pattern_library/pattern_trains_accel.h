#pragma once

#include "../pattern_internals/pattern.h"

typedef struct {
    int pos;
    int speed;
    int topSpeed;
    int tail;
    int hue;
    int acceleration;
} Train_Accel;

class Pattern_Trains_Accel: public Pattern {
public:
    void loop();
    void init();
private:
    const static int NUM_TRAINS = 12;
    const static int TRAIL_LENGTH = 10;
    const static int MAX_SPEED = 10;
    const static int ACCELERATION_CYCLE = 10; //number of loop cycles to wait to update speed
    const static int ACCELERATE_CHANCE = 10; //1 / (chance that a train will begin to move again)
    const static int DECELERATE_CHANCE = 20; //1 / (chance that a train will begin to stop)

    int targetTail(Train_Accel *train);

    Train_Accel trains[NUM_TRAINS];
    int cycle; //index in the acceleration cycle (counts down to 0)
};
