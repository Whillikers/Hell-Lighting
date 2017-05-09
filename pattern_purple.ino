void pattern_purple() {
  clearLEDs();
  int g = 0;
  while (true) {
    if (escape) return;
    FastLED.setBrightness(BRIGHTNESS_MAX);
  
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      leds[transform(i)] = ((i + g) % 3 == 0) ? CRGB::Purple : CRGB::Black;
    }
  
    FastLED.show();
    g = (g + 1) % 3;
    delay(analogRead(PIN_POT) / 10 + 1);
  }
}
