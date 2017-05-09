void pattern_white_stars(){
  /*
  This is a night sky pattern that more or less randomly turns led's on and off. 
  everyonce and a while (ballpark 16 minutes) there will be a "special event"
  that has the potential to turn on or off a very large number of LEDs. 
  
  pot -> used to determine the ratio of led's turned off to led's turned on. 
  */
  clearLEDs();
  FastLED.setBrightness(BRIGHTNESS_MAX / 2);

  while (true) {
    if (escape) return;
    
    int scalenumber = 100; // determines how many total operations are conducted per tick of the program. 
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
