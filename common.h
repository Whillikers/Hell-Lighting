/*
 * common.h:
 *  Provides a set of constants, functions, and settings useful
 *  for writing patterns but without much physical significance.
 */

#pragma once

#include "topology.h"
#include "hardware.h"

#define FASTLED_INTERNAL
#include <FastLED.h>

/*
 * Globals
 */
// Array of all leds taken as one strip, from the inner right corner and going clockwise
extern CRGB leds[NUM_LEDS_TOTAL];

/*
 * Constants
 */
#define BRIGHTNESS_MAX 100

/*
 * Functions
 */
// Sets all active LEDs to black
void clearLEDs();

/*
 * Take an LED index and transform it, given that the third and
 * fourth strips are reversed, into an index which will work on
 * the led array
 */
int transform(int index);
