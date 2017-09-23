#include "hell_lighting.h"

#include "pattern.h"
#include "pattern_color.h"
#include "pattern_colorloop.h"

#define NUM_PATTERNS 2

// Pattern list //
Pattern* patterns[NUM_PATTERNS];

void patternInit() {
    patterns[0] = (Pattern*) new Pattern_Color();
    patterns[1] = (Pattern*) new Pattern_Colorloop();
}

