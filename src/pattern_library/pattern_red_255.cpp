#include "pattern_red_255.h"

void Pattern_red_255::init() {   
    make_red();
    make_false();
    FastLED.setBrightness(BRIGHTNESS_MAX);
}

void Pattern_red_255::loop() {
  make_red();
  int potValue = analogRead(PIN_POT);
  if (potValue = POT_MAX - 10){
    for (int i = 0; i < NUM_LEDS_TOTAL / 3; i++){
      int n = random16(NUM_LEDS_TOTAL);
      if (random8(3) > 0 ){
        is_random[n] = true;
      } else {
        is_random[n] = false;
      }
    }
  }

  
  for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
    if (is_random[i]){
      leds[i].r = random8(255);
      leds[i].g = random8(255);
      leds[i].b = random8(255);
    }
  }
  FastLED.show();
}

void Pattern_red_255::make_red() {
  for (int i = 0; i < NUM_LEDS_TOTAL; i++){
    leds[i].r = 255;
    leds[i].g = 0;
    leds[i].b = 0;
  }
}

void Pattern_red_255::make_false() {
  for (int i = 0; i < NUM_LEDS_TOTAL; i++){
    is_random[i] = false;
  }
}

