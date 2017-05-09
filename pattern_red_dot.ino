void pattern_red_dot() {
  /*
  This pattern sends a small red pulse traveling around in a circle. Has persistence
  of vission effects at higher speeds. 
  
  POT -> change dot speed. 
  */
  FastLED.setBrightness(BRIGHTNESS_MAX);
  clearLEDs();
  
  while (true) {
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      if (escape) return;
      leds[transform(i)] = CRGB::Red;
      leds[transform(i + 1)] = CRGB::Red;
      leds[transform(i - 1)] = CRGB::Black;
      FastLED.show();
      delay(map(analogRead(PIN_POT), 0, POT_MAX, 1, 120));
    }
  }
}
