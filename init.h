#include "hell_lighting.h"

#include "pattern.h"
#include "pattern_color.h"
#include "pattern_colorloop.h"
#include "pattern_colorwheel.h"
#include "pattern_drift.h"
#include "pattern_fire.h"
#include "pattern_purple.h"
#include "pattern_race.h"
#include "pattern_red_dot.h"
#include "pattern_rule110.h"
#include "pattern_trains.h"
#include "pattern_white_stars.h"

#define NUM_PATTERNS 11

// Pattern list //
Pattern* patterns[NUM_PATTERNS];

void patternInit() {
    patterns[0] = (Pattern*) new Pattern_Color();
    patterns[1] = (Pattern*) new Pattern_Colorloop();
    patterns[1] = (Pattern*) new Pattern_Colorwheel();
    patterns[2] = (Pattern*) new Pattern_Drift();
    patterns[3] = (Pattern*) new Pattern_Fire();
    patterns[4] = (Pattern*) new Pattern_Purple();
    patterns[5] = (Pattern*) new Pattern_Race();
    patterns[6] = (Pattern*) new Pattern_Red_Dot();
    patterns[7] = (Pattern*) new Pattern_Rule110();
    patterns[8] = (Pattern*) new Pattern_Trains();
    patterns[9] = (Pattern*) new Pattern_White_Stars();
}

