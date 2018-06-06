/*
 * hell_lighting.h:
 *  Provides common constants, globals, etc useful internally but
 *  not commonly used elsewhere.
 */

#pragma once

#include "src/pattern_internals/pattern.h"
#include <setjmp.h>

// Debug switches //
// #define DEBUG 1
// #define DEBUG_POT 1

// Settings //
#define BRIGHTNESS_MAX 100
#define PATTERN_DEFAULT color

// Internals //
// TODO: Clean up global state with abstractions
int currentPatternIndex;
int nextPatternIndex; // Used to keep track of the next pattern to be displayed. Usually equal to currentPatternIndex.
Pattern* currentPattern;
jmp_buf jumpPoint; // Used for escaping functions
