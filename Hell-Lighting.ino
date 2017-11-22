/*
 * Hell-Lighting.ino:
 *   Internal code for the system's main operation, including running patterns
 *   and handling interface interaction.
 */

#include "src/config/init.h"

// Define led array
CRGB leds[NUM_LEDS_TOTAL];

// Automatic functions //
void setup() {
  // Debug stuff //
  #ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Beginning setup");
  #endif

  // Interface setup //
  // Assign pins //
  // TODO: Move to board abstraction
  pinMode(PIN_BUTTON_RESET, INPUT);
  pinMode(PIN_BUTTON_NEXT, INPUT);
  pinMode(PIN_BUTTON_PREV, INPUT);
  // Set up interrupts //
  pciSetup(PIN_BUTTON_NEXT);
  pciSetup(PIN_BUTTON_PREV);

  // LED setup //
  // Add separate LED strips to the array //
  // TODO: Move to system abstraction
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

// Initializes and runs a pattern continuously; called once per pattern switch
void runPattern() {
  setjmp(jumpPoint);

  #ifdef DEBUG
  Serial.println("Running a new pattern:");
  Serial.println(currentPatternIndex);
  #endif

  interrupts();

  int counter = 0;

  currentPattern = patternFactories[currentPatternIndex]->getInstance();
  currentPattern->init();

  #ifdef DEBUG
  Serial.println("Pattern finished init");
  #endif

  while (!currentPattern->isFinished()) {
    currentPattern->loop();

    #ifdef DEBUG
    Serial.println("Pattern finished loop frame");
    #endif
  }

  #ifdef DEBUG
  Serial.println("Pattern finished internally");
  #endif

  counter = 0;
  cleanupPattern();
  currentPatternIndex++;
  if (currentPatternIndex >= NUM_PATTERNS) currentPatternIndex = 0;
  longjmp(jumpPoint, 1); // End the current pattern and load a new one
}

void cleanupPattern() {
    currentPattern->cleanup();
    free(currentPattern);
}

// TODO: Move to pattern abstraction (pattern software reset)
void reset() {
  #ifdef DEBUG
  Serial.println("Resetting system");
  #endif

  // Initialize values //
  currentPatternIndex = 0;
  clearLEDs();
  runPattern();
}

/*
 * Enable pin-change interrupts on arbitrary pins;
 * taken from http://playground.arduino.cc/Main/PinChangeInterrupt
 * TODO: Move to board abstraction
 */
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
// TODO: Remove??
ISR (PCINT1_vect) {}

// Button-press behaviors //
// TODO: Change to pattern-change behavior and make hardware-agnostic; call board triggers
void nextButton() {
  if (!digitalRead(PIN_BUTTON_NEXT)) return; // We only want to detect a rising edge
  cleanupPattern();
  currentPatternIndex++;
  if (currentPatternIndex >= NUM_PATTERNS) currentPatternIndex = 0;
  longjmp(jumpPoint, 1); // End the current pattern and load a new one
}

void previousButton() {
  if (!digitalRead(PIN_BUTTON_PREV)) return; // We only want to detect a rising edge
  cleanupPattern();
  currentPatternIndex--;
  if (currentPatternIndex < 0) currentPatternIndex = NUM_PATTERNS - 1;
  longjmp(jumpPoint, 1); // End the current pattern and load a new one
}
