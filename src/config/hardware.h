/*
 * hardware.h:
 *  Provides information about the system hardware useful
 *  for writing patterns.
 */

#pragma once

// Sensor constants //
#define POT_MAX 1023

// Pins //
// Pattern-switching //
#define PIN_BUTTON_RESET 2
#define PIN_BUTTON_NEXT 18 // TODO: Rewire to an interrupt pin
#define PIN_BUTTON_PREV 11
#define PIN_ENCODER_A   15
#define PIN_ENCODER_B   19 
// Inputs //
#define PIN_POT A0
// LED //
#define PIN_LED_1 3
#define PIN_LED_2 0
#define PIN_LED_3 1
#define PIN_LED_4 2
