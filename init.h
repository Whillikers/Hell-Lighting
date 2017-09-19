#include "hell_lighting.h"

#define NUM_PATTERNS 11

// Pattern list //
void (*patterns[NUM_PATTERNS])(void);
extern void pattern_color();
extern void pattern_purple();
extern void pattern_red_dot();
extern void pattern_fire();
extern void pattern_white_stars();
extern void pattern_rule110();
extern void pattern_colorloop();
extern void pattern_trains();
extern void pattern_colorwheel();
extern void pattern_race();
extern void pattern_drift();

void patternInit() {
  patterns[0] = pattern_color;
  patterns[1] = pattern_purple;
  patterns[2] = pattern_red_dot;
  patterns[3] = pattern_fire;
  patterns[4] = pattern_white_stars;
  patterns[5] = pattern_rule110;
  patterns[6] = pattern_colorloop;
  patterns[7] = pattern_trains;
  patterns[8] = pattern_colorwheel;
  patterns[9] = pattern_race;
  patterns[10] = pattern_drift;
}

