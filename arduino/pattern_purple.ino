void pattern_purple() {
  clearLEDs();
  int g = 0;
  FastLED.setBrightness(BRIGHTNESS_MAX);
  
  while (true) {
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      leds[transform(i)] = ((i + g) % 3 == 0) ? CRGB::Purple : CRGB::Black;
    }
  
    FastLED.show();
    g = (g + 1) % 3;
    delay(map(analogRead(PIN_POT), 0, POT_MAX, 1, 150));
  }
}
