/*
 * hell_lighting.h:
 *  Provides common constants, globals, etc useful internally but
 *  not commonly used elsewhere.
 */

#pragma once

#include "pattern.h"

// Debug switches //
// #define DEBUG 1
// #define DEBUG_POT 1

// Pins //
// Interface //
#define PIN_BUTTON_RESET 2
#define PIN_BUTTON_NEXT 4
#define PIN_BUTTON_PREV 11
// Inputs //
#define PIN_POT A0
// LED //
#define PIN_LED_1 9
#define PIN_LED_2 8
#define PIN_LED_3 6
#define PIN_LED_4 7

// Settings //
#define PATTERN_DEFAULT color

// Globals //
CRGB leds[NUM_LEDS_TOTAL]; // Array of all leds taken as one strip, from the inner right corner and going clockwise
int currentPatternIndex;
jmp_buf jumpPoint; // Used for escaping functions
