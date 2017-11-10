#pragma once

#include "../pattern.h"

class Pattern_Flicker: public Pattern {
public:
    void loop();
    void init();
private:
    const static int lights_per_side = 10;
    const static int len_gap = 15;
    const static int len_light = 42;
    const static int maxframes_wait = 500;
    const static int maxframes_flicker = 20;
    int countdowns_left[lights_per_side]; // Countdown until a flicker
    int countdowns_right[lights_per_side];
    int durations_left[lights_per_side]; // Duration of a flicker
    int durations_right[lights_per_side];
};
