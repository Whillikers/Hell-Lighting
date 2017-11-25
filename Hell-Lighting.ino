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
  pinMode(PIN_ENCODER_A, INPUT);
  pinMode(PIN_ENCODER_B, INPUT);
  DDRK = B11111111;
  // Set up interrupts //
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_NEXT), nextPattern, HIGH);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_B), patternSwitchEncoder, CHANGE);

  // LED setup //
  // Add separate LED strips to the array //
  // TODO: Move to system abstraction
  FastLED.addLeds<APA104, PIN_LED_1, GRB>(leds, 0, NUM_LEDS_1);
  FastLED.addLeds<APA104, PIN_LED_2, GRB>(leds, NUM_LEDS_1, NUM_LEDS_2);
  FastLED.addLeds<APA104, PIN_LED_3, GRB>(leds, NUM_LEDS_1 + NUM_LEDS_2, NUM_LEDS_3);
  FastLED.addLeds<APA104, PIN_LED_4, GRB>(leds, NUM_LEDS_1 + NUM_LEDS_2 + NUM_LEDS_3, NUM_LEDS_4);

  // Initialize pattern ordering //
  currentPatternIndex = 0;
  nextPatternIndex = currentPatternIndex;
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
    delay(1);
    if (nextPatternIndex != currentPatternIndex){
      noInterrupts();
      currentPatternIndex = nextPatternIndex;
      updatePattern();
    }
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

// Button-press behaviors //
void nextPattern() {
  cleanupPattern();
  currentPatternIndex++;
  if (currentPatternIndex >= NUM_PATTERNS) currentPatternIndex = 0;
  displayPatternNumber(currentPatternIndex);
  longjmp(jumpPoint, 1); // End the current pattern and load a new one
}

void updatePattern() {
  cleanupPattern();
  displayPatternNumber(currentPatternIndex);
  longjmp(jumpPoint, 1); // End the current pattern and load a new one
}


void patternSwitchEncoder(){
  /*
   * This is the serial interrupt routine for the pattern switching encoder. It is responcible for deboucning
   * the encoder and determining the encoder's direction of travel. Note, that in an effort to prevent false
   * direction changes the debounce interval is shorter for pulses in the same direction than for direciton changes.
   * In user testing this was found to produce the best results, but it can always be dissabled by setting the two 
   * intervals to the same value. 
   */
    #define INTERVAL_CHANGE  100 //ms before another move in the other direction will be considered. 
    #define INTERVAL_SAME    80 //ms before another move in the same direction will be considered. 
    static unsigned int previousTime = 0;
    static bool clockwise = true; // keep track of last direction
    bool currentDirection = true;
    
    bool A = digitalRead(PIN_ENCODER_A);
    bool B = digitalRead(PIN_ENCODER_B);
    if (A == B){
      currentDirection = true;
    } else {
      currentDirection = false;
    }
    if (unsigned(millis() - previousTime) > INTERVAL_CHANGE || clockwise == currentDirection && unsigned(millis() - previousTime) > INTERVAL_SAME){
      if(currentDirection){
        // increment current pattern number. 
        nextPatternIndex++;
        if (nextPatternIndex >= NUM_PATTERNS) nextPatternIndex = 0;
      } else {
        //decriment current pattern number. 
        nextPatternIndex--;
        if (nextPatternIndex < 0) nextPatternIndex = NUM_PATTERNS - 1;
      }
      displayPatternNumber(nextPatternIndex);
      
     previousTime = millis();
     clockwise = currentDirection;
    }
}


void displayPatternNumber(int patternNumber){
  /*
   * This function displays the a value on the pattern number display. 
   * pre-condition: register "DDRK" which controls the pin mode must be set to output mode for all pins. 
   * 
   */
  PORTK = lowByte(patternNumber);
}

