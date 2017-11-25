/*
 * init.h:
 *  Defines the set of patterns and their order, as well as initializing
 *  patterns.
 */

#pragma once

#include "../../hell_lighting.h"

#include "../pattern_library/pattern_color.h"
#include "../pattern_library/pattern_colorloop.h"
#include "../pattern_library/pattern_colorwheel.h"
#include "../pattern_library/pattern_drift.h"
#include "../pattern_library/pattern_drops.h"
#include "../pattern_library/pattern_fire.h"
#include "../pattern_library/pattern_purple.h"
#include "../pattern_library/pattern_race.h"
#include "../pattern_library/pattern_red_dot.h"
#include "../pattern_library/pattern_rule110.h"
#include "../pattern_library/pattern_trains.h"
#include "../pattern_library/pattern_white_stars.h"
#include "../pattern_library/pattern_red_255.h"
#include "../pattern_library/pattern_flicker.h"
#include "../pattern_library/pattern_binary.h"
#include "../pattern_library/pattern_trains_accel.h"

#define NUM_PATTERNS 16

// Pattern factory list //
Factory* patternFactories[NUM_PATTERNS];

void patternInit() {
    patternFactories[0] = (Factory*) new PatternFactory<Pattern_Color>();
    patternFactories[1] = (Factory*) new PatternFactory<Pattern_Colorloop>();
    patternFactories[2] = (Factory*) new PatternFactory<Pattern_Colorwheel>();
    patternFactories[3] = (Factory*) new PatternFactory<Pattern_Drift>();
    patternFactories[4] = (Factory*) new PatternFactory<Pattern_Fire>();
    patternFactories[5] = (Factory*) new PatternFactory<Pattern_Purple>();
    patternFactories[6] = (Factory*) new PatternFactory<Pattern_Race>();
    patternFactories[7] = (Factory*) new PatternFactory<Pattern_Red_Dot>();
    patternFactories[8] = (Factory*) new PatternFactory<Pattern_Rule110>();
    patternFactories[9] = (Factory*) new PatternFactory<Pattern_Trains>();
    patternFactories[10] = (Factory*) new PatternFactory<Pattern_White_Stars>();
    patternFactories[11] = (Factory*) new PatternFactory<Pattern_Flicker>();
    patternFactories[12] = (Factory*) new PatternFactory<Pattern_Binary>();
    patternFactories[13] = (Factory*) new PatternFactory<Pattern_red_255>();
    patternFactories[14] = (Factory*) new PatternFactory<Pattern_Drops>();
    patternFactories[15] = (Factory*) new PatternFactory<Pattern_Trains_Accel>();
}

