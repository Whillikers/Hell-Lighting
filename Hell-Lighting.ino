#include <FastLED.h>
#include <setjmp.h>
#include "init.h"

// Automatic functions //
void setup() {
  // Debug stuff //
  #ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Beginning setup");
  #endif
  
  // Interface setup //
  // Assign pins //      
  pinMode(PIN_BUTTON_RESET, INPUT);
  pinMode(PIN_BUTTON_NEXT, INPUT);
  pinMode(PIN_BUTTON_PREV, INPUT);
  // Set up interrupts //
  pciSetup(PIN_BUTTON_NEXT); // TODO: Rewire to an interrupt pin
  pciSetup(PIN_BUTTON_PREV);

  // LED setup //
  // Add separate LED strips to the array //
  FastLED.addLeds<APA104, PIN_LED_1, GRB>(leds, 0, NUM_LEDS_1);
  FastLED.addLeds<APA104, PIN_LED_2, GRB>(leds, NUM_LEDS_1, NUM_LEDS_2);
  FastLED.addLeds<APA104, PIN_LED_3, GRB>(leds, NUM_LEDS_1 + NUM_LEDS_2, NUM_LEDS_3);
  FastLED.addLeds<APA104, PIN_LED_4, GRB>(leds, NUM_LEDS_1 + NUM_LEDS_2 + NUM_LEDS_3, NUM_LEDS_4);

  // Initialize pattern ordering //
  currentPatternIndex = 0;
  patternInit();
  
  // Rest of setup is handled in reset() //
  reset();
}

void loop() {}

void runPattern() {
  setjmp(jumpPoint);
  
  #ifdef DEBUG
  Serial.println("Running a new pattern:");
  Serial.println(currentPatternIndex);
  #endif
  
  interrupts();

  int counter = 0;

  Pattern* currentPattern = patterns[currentPatternIndex];
  currentPattern->init();
  while (!currentPattern->isFinished()) {
    currentPattern->loop();
  }
  
  counter = 0;
  currentPattern->cleanup();
  currentPatternIndex++;
  if (currentPatternIndex >= NUM_PATTERNS) currentPatternIndex = 0;
  longjmp(jumpPoint, 1); // End the current pattern and load a new one
}

void reset() {
  #ifdef DEBUG
  Serial.println("Resetting");
  #endif
  
  // Initialize values //
  currentPatternIndex = 0;
  clearLEDs();
  runPattern();
}

// Enable pin-change interrupts on arbitrary pins; taken from http://playground.arduino.cc/Main/PinChangeInterrupt //
void pciSetup(byte pin) {
  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
  PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
  PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

// This interrupt handles the "previous button" behavior on pin D11 //
ISR (PCINT0_vect) { // Pin-interrupt handler for D8 to D13    
  noInterrupts();
  previousButton();
}

// This interrupt handles the "next button" behavior on pin D4 //
ISR (PCINT2_vect) { // Pin-interrupt handler for D0 to D7
  noInterrupts();
  nextButton();
}

// The analog pin-interrupt is unused //
ISR (PCINT1_vect) {}

// Button-press behaviors //
void nextButton() {
  if (!digitalRead(PIN_BUTTON_NEXT)) return; // We only want to detect a rising edge
  patterns[currentPatternIndex]->cleanup();
  currentPatternIndex++;
  if (currentPatternIndex >= NUM_PATTERNS) currentPatternIndex = 0;
  longjmp(jumpPoint, 1); // End the current pattern and load a new one
}

void previousButton() {
  if (!digitalRead(PIN_BUTTON_PREV)) return; // We only want to detect a rising edge
  patterns[currentPatternIndex]->cleanup();
  currentPatternIndex--;
  if (currentPatternIndex < 0) currentPatternIndex = NUM_PATTERNS - 1;
  longjmp(jumpPoint, 1); // End the current pattern and load a new one
}
