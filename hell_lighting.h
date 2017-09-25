/*
 * hell_lighting.h:
 *  Provides common constants, globals, etc useful internally but
 *  not commonly used elsewhere.
 */

#pragma once

#include "common.h"
#include <setjmp.h>

// Debug switches //
// #define DEBUG 1
// #define DEBUG_POT 1

// Settings //
#define BRIGHTNESS_MAX 100
#define PATTERN_DEFAULT color

// Internals //
int currentPatternIndex;
jmp_buf jumpPoint; // Used for escaping functions
