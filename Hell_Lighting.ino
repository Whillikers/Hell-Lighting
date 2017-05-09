#include <FastLED.h>

// Debug switches //
// #define DEBUG 1
// #define DEBUG_POT 1

// System parameters //
#define NUM_LEDS_1 332
#define NUM_LEDS_2 285
#define NUM_LEDS_3 355
#define NUM_LEDS_4 251
#define NUM_LEDS_MAX 355
#define NUM_LEDS_TOTAL (332 + 285 + 355 + 251)
#define NUM_PATTERNS 6

// Hardware Constants //
#define POT_MAX 1023

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
int f, g, h;

// Pattern list //
void (*patterns[NUM_PATTERNS])(void);

// Settings //
#define BRIGHTNESS_MAX 100
#define PATTERN_DEFAULT color

// Globals //
CRGB leds[NUM_LEDS_TOTAL]; // Array of all leds taken as one strip, from the inner right corner and going clockwise
uint8_t brightness;
int currentPatternIndex;

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
  pciSetup(PIN_BUTTON_NEXT);
  pciSetup(PIN_BUTTON_PREV);

  // LED setup //
  // Add separate LED strips to the array //
  FastLED.addLeds<APA104, PIN_LED_1, GRB>(leds, 0, NUM_LEDS_1);
  FastLED.addLeds<APA104, PIN_LED_2, GRB>(leds, NUM_LEDS_1, NUM_LEDS_2);
  FastLED.addLeds<APA104, PIN_LED_3, GRB>(leds, NUM_LEDS_1 + NUM_LEDS_2, NUM_LEDS_3);
  FastLED.addLeds<APA104, PIN_LED_4, GRB>(leds, NUM_LEDS_1 + NUM_LEDS_2 + NUM_LEDS_3, NUM_LEDS_4);

  // Initialize pattern ordering //
  patterns[0] = pattern_color;
  patterns[1] = pattern_pulse;
  patterns[2] = pattern_purple;
  patterns[3] = pattern_red_dot;
  patterns[4] = pattern_fire;
  patterns[5] = pattern_white_stars;
  currentPatternIndex = 0;

  // Rest of setup is handled in reset() //
  reset();
  runPattern();
}

void loop() {
  //runPattern();
}

void runPattern() {
  FastLED.setBrightness(brightness);
  patterns[currentPatternIndex]();
}

void reset() {
  #ifdef DEBUG
  Serial.println("Resetting");
  #endif
  
  // Initialize values //
  brightness = BRIGHTNESS_MAX;
  currentPatternIndex = 0;
  f = 0;
  g = 0;
  h = 0;

  FastLED.setBrightness(brightness);
  clearLEDs();
}

// Sets all active LEDs to black //
void clearLEDs() {
  #ifdef DEBUG
  Serial.println("Clearing active LEDs");
  #endif

  for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

// Pattern functions //
void pattern_color() {
  while (true) {
    FastLED.setBrightness(brightness);
    CHSV col = CHSV(min(analogRead(PIN_POT) / 4, 255), 255, 255);
    brightness = BRIGHTNESS_MAX;

    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      leds[transform(i)] = col;
    }

    FastLED.show();
    delay(10);
  }
}

void pattern_pulse() {
  while (true) {
    if (g <= 0) {
      g = 1;
      f = 1;
    } else if (g >= 100) {
      g = 99;
      f = 0;
    }
    if (f) {
      g += analogRead(PIN_POT) / 14;
    } else {
      g -= analogRead(PIN_POT) / 14;
    }
  
    brightness = ((float) BRIGHTNESS_MAX) * cos(((float) g) * 3.1 / 200.0);
  
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      leds[transform(i)] = CRGB::Cyan;
    }
  
    FastLED.show();
    delay(10);
  }
}

void pattern_purple() {
  while (true) {
    brightness = BRIGHTNESS_MAX;
  
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      leds[transform(i)] = ((i + g) % 3 == 0) ? CRGB::Purple : CRGB::Black;
    }
  
    FastLED.show();
    g = (g + 1) % 3;
    delay(analogRead(PIN_POT) / 10 + 1);
  }
}

void pattern_red_dot() {
  /*
  This pattern sends a small red pulse traveling around in a circle. Has persistence
  of vission effects at higher speeds. 
  
  POT -> change dot speed. 
  */
  brightness = BRIGHTNESS_MAX;
  clearLEDs();

  while (true) {
    if (!g) {
      leds[0] = CRGB::Red;
      leds[NUM_LEDS_TOTAL - 1] = CRGB::Black;
    } else {
      leds[transform(g + 1)] = CRGB::Red;
      leds[transform(g)] = CRGB::Red;
      leds[transform(g - 1)] = CRGB::Black;
    }
    
    FastLED.show();
    g = (g + 1) % (NUM_LEDS_TOTAL - 1);
    Serial.println(g);
    delay(max(analogRead(PIN_POT) / 10, 1));
  }
}

void pattern_white_stars(){
  /*
  This is a night sky pattern that more or less randomly turns led's on and off. 
  everyonce and a while (ballpark 16 minutes) there will be a "special event"
  that has the potential to turn on or off a very large number of LEDs. 
  
  pot -> used to determine the ratio of led's turned off to led's turned on. 
  */
  clearLEDs();

  while (true) {
    brightness = BRIGHTNESS_MAX / 2;
    int scalenumber = 100; // determines how many total operations are conducted per
                 // tick of the program. 
    int specialFrequency = 20000; // how many ticks (on average) between special events.
    int potValue = analogRead(PIN_POT);
  
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      if (leds[i].r != 0) { //Fade
        int fade = 50;
  
        if (leds[i].r <= fade) {
          leds[i] = CRGB::Black;
          continue;
        }
        
        leds[i].r -= fade;
        leds[i].g -= fade;
        leds[i].b -= fade;
        continue;
      }
  
      int r = random(512);
      if (r > potValue) leds[i] = CRGB::White;
    }
               
    /*
    // delete some number of currently bright LEDs.
    for (int i = 0; i < random(potValue / scalenumber); i++){
      leds[random(NUM_LEDS_TOTAL)] = CRGB::Black;
    }
    
    // set some number of leds to be white. 
    for (int i = 0; i < random((POT_MAX - potValue) / scalenumber); i++){
      leds[random(NUM_LEDS_TOTAL)] = CRGB::White; 
    }
    */
    
    // periodically have a large increase or decrease in the number of lights.
    if (random(specialFrequency) == 0){
      if (random(1) == 1){
        for(int i = 0; i < random(NUM_LEDS_TOTAL); i++){
          leds[random(NUM_LEDS_TOTAL)] = CRGB::Black;
        }
      } else {
        for(int i = 0; i < random(NUM_LEDS_TOTAL); i++){
          leds[random(NUM_LEDS_TOTAL)] = CRGB::Black;
        }
      }
    }
    FastLED.show();
    delay(25);
  }
} 


void pattern_fire() {
  int x;
  while (true) {
    brightness = max((float) BRIGHTNESS_MAX * (((float) (1024 - analogRead(PIN_POT))) / 1024.0), 5);
    for (int i = 1; i < NUM_LEDS_TOTAL - 1; i++) {
      if (leds[i].r == 0) { // This point has not yet been initialized
        leds[i] = CRGB(random(100, 255), random(0, 50), 0);
      } else { // Standard fire algorithm
        x = ((leds[i-1].r - leds[i].r) - (leds[i + 1].r - leds[i].r)) / 4;
        leds[i].r = x + random(100, 255);
        leds[i].g = random(0, 20);
        leds[i].b = 0;
      }
    }
  
    FastLED.show();
    delay(1);
  }
}

// Helper functions //
// Take an LED index and transform it, given that the third and fourth strips are reversed, into an index which will work on the led array //
int transform(int index) {
  if (index < NUM_LEDS_1 + NUM_LEDS_2) return index;
  if (index < NUM_LEDS_1 + NUM_LEDS_2 + NUM_LEDS_3) return 2 * NUM_LEDS_1 + 2 * NUM_LEDS_2 + NUM_LEDS_3 - index - 1;
  return 2 * NUM_LEDS_1 + 2 * NUM_LEDS_2 + 2 * NUM_LEDS_3 + NUM_LEDS_4 - index - 1;
}

// Enable pin-change interrupts on arbitrary pins; taken from http://playground.arduino.cc/Main/PinChangeInterrupt //
void pciSetup(byte pin) {
  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
  PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
  PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

// This interrupt handles the "previous button" behavior on pin D11 //
ISR (PCINT0_vect) { // Pin-interrupt handler for D8 to D13    
  previousButton();
}

// This interrupt handles the "next button" behavior on pin D4 //
ISR (PCINT2_vect) { // Pin-interrupt handler for D0 to D7
  nextButton();
}

// The analog pin-interrupt is unused //
ISR (PCINT1_vect) {}

// Button-press behaviors //
void nextButton() {
  if (!digitalRead(PIN_BUTTON_NEXT)) return; // We don't want to detect a falling edge
  currentPatternIndex++;
  if (currentPatternIndex >= NUM_PATTERNS) currentPatternIndex = 0;
  runPattern();
}

void previousButton() {
  if (!digitalRead(PIN_BUTTON_PREV)) return; // We don't want to detect a falling edge
  currentPatternIndex--;
  if (currentPatternIndex < 0) currentPatternIndex = NUM_PATTERNS - 1;
  runPattern();
}

