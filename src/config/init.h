/*
 * init.h:
 *  Defines the set of patterns and their order, as well as initializing
 *  patterns.
 */

#pragma once

#include "../../hell_lighting.h"

#include "../patterns/pattern_color.h"
#include "../patterns/pattern_colorloop.h"
#include "../patterns/pattern_colorwheel.h"
#include "../patterns/pattern_drift.h"
#include "../patterns/pattern_drops.h"
#include "../patterns/pattern_fire.h"
#include "../patterns/pattern_purple.h"
#include "../patterns/pattern_race.h"
#include "../patterns/pattern_red_dot.h"
#include "../patterns/pattern_rule110.h"
#include "../patterns/pattern_trains.h"
#include "../patterns/pattern_white_stars.h"
#include "../patterns/pattern_red_255.h"
#include "../patterns/pattern_flicker.h"
#include "../patterns/pattern_binary.h"

#define NUM_PATTERNS 15

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

    // TODO: Convert to new pattern
    // patterns[13] = (Pattern*) new Pattern_Trains(true);
}

