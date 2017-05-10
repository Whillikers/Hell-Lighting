void pattern_colorwheel() {
  clearLEDs();
  FastLED.setBrightness(BRIGHTNESS_MAX);
  int pos = 0;
  
  while (true) {
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
      leds[transform(i)] = CHSV(map(i + pos, 0, NUM_LEDS_TOTAL, 0, 255), 255, 255);
    }

    pos += map(analogRead(PIN_POT), 0, POT_MAX, 0, 50);
    if (pos >= NUM_LEDS_TOTAL) pos -= NUM_LEDS_TOTAL;
    FastLED.show();
    delay(10);
  }
}
