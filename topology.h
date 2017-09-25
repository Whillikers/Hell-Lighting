/*
 * topology.h:
 *  Provides information about common locations and sizes
 *  in the system useful for making patterns.
 */

#pragma once

// Locations by transformed index //
#define ARCH_START 0
#define ARCH_END 43
#define LEFT_START 44
#define LEFT_END 616
#define FAR_START 617
#define FAR_END 651
#define RIGHT_START 1222
#define RIGHT_END 652

// Strip parameters //
#define NUM_LEDS_1 332
#define NUM_LEDS_2 285
#define NUM_LEDS_3 356 //355
#define NUM_LEDS_4 254 // 251
#define NUM_LEDS_MAX 356

// Generally useful constants
#define NUM_LEDS_TOTAL (NUM_LEDS_1 + NUM_LEDS_2 + NUM_LEDS_3 + NUM_LEDS_4) // 1226
