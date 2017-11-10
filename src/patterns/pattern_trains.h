#pragma once

#include "../pattern.h"

typedef struct {
    int pos;
    int speed;
    int topSpeed;
    int tail;
    int hue;
    int acceleration;
} Train;

class Pattern_Trains: public Pattern {
public:
    void loop();
    void init();
    // TODO: Recreate accelerating trains
    Pattern_Trains();
private:
    const static int NUM_TRAINS = 12;
    const static int TRAIL_LENGTH = 10;
    const static int MAX_SPEED = 10;
    const static int ACCELERATION_CYCLE = 10; //number of loop cycles to wait to update speed
    const static int ACCELERATE_CHANCE = 10; //1 / (chance that a train will begin to move again)
    const static int DECELERATE_CHANCE = 20; //1 / (chance that a train will begin to stop)

    int targetTail(Train *train);

    Train trains[NUM_TRAINS];
    bool accelerate;
    int cycle; //index in the acceleration cycle (counts down to 0)
};
