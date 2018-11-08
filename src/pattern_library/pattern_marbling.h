#pragma once

#include "../pattern_internals/pattern.h"

class Pattern_Marbling: public Pattern {
public:
    void loop();
    void init();
private:
    const int brightness_levels = 5;
    const int min_brightness = 40;
    const int brightness_step = (255 - min_brightness) / brightness_levels;
    int led_groups = 4;
    int group = 0;
    int hue;
};
