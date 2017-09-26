//Randomly sets lights to on or off,
//then updates them based on number of neighbors

#include "pattern_gameoflife.h"

void Pattern_GameOfLife::init() {
  clearLEDs();
  FastLED.setBrightness(BRIGHTNESS_MAX);
  for (int i = 0; i < NUM_LEDS_TOTAL; i++) occupied[i] = random(0, 2);
}

void Pattern_GameOfLife::loop() {
  bool oldOccupied[NUM_LEDS_TOTAL];
  memcpy(oldOccupied, occupied, sizeof(occupied));
  for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
    int neighbors = 0;
    if (i > 0 && oldOccupied[i - 1]) neighbors++;
    if (oldOccupied[i]) neighbors++;
    if (i + 1 < NUM_LEDS_TOTAL && oldOccupied[i + 1]) neighbors++;
    occupied[i] = neighbors == 1;
    leds[transform(i)] = occupied[i] ? CRGB::White : CRGB::Black;
  }
  FastLED.show();
  delay(500);
}