void pattern_color() {
  clearLEDs();
  CHSV col;
  FastLED.setBrightness(BRIGHTNESS_MAX);
  
  while (true) {
    if (escape) return;

    col = CHSV(map(analogRead(PIN_POT), 0, POT_MAX, 0, 255), 255, 255);
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      leds[transform(i)] = col;
    }

    FastLED.show();
    delay(10);
  }
}
