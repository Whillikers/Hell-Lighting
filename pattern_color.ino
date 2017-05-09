void pattern_color() {
  clearLEDs();
  while (true) {
    if (escape) return;
    FastLED.setBrightness(BRIGHTNESS_MAX);
    CHSV col = CHSV(min(analogRead(PIN_POT) / 4, 255), 255, 255);

    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      leds[transform(i)] = col;
    }

    FastLED.show();
    delay(10);
  }
}
