#pragma once

#include "../pattern.h"

typedef struct {
    int pos;
    int speed;
    int topSpeed;
    int tail;
    int hue;
} Train;

class Pattern_Trains: public Pattern {
public:
    void loop();
    void init();
private:
    const static int NUM_TRAINS = 12;
    const static int TRAIL_LENGTH = 10;
    const static int MAX_SPEED = 10;

    int targetTail(Train *train);

    Train trains[NUM_TRAINS];
};
