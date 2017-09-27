//Randomly colored drops expand from a point and slow down,
//and are then set back to black from the middle out

#include "pattern_drops.h"

Drop newDrop() {
  Drop drop;
  drop.center = random(0, NUM_LEDS_TOTAL);
  drop.color = CHSV(random(0, 256), 255, 255);
  drop.receding = false;
  drop.start = millis();
  drop.duration = random(MIN_DURATION, MAX_DURATION);
  drop.maxSize = random(0, MAX_SIZE);
  return drop;
}

void Pattern_Drops::init() {
  clearLEDs();
  FastLED.setBrightness(BRIGHTNESS_MAX);
  for (int i = 0; i < NUM_DROPS; i++) drops[i] = newDrop();
}

void Pattern_Drops::loop() {
  long now = millis();
  for (int i = 0; i < NUM_DROPS; i++) {
    Drop drop = drops[i];
    double timeFraction = (double)(now - drop.start) / (double)drop.duration;
    int size = (int)(drop.maxSize * (1 - exp(-DECAY * timeFraction)));
    if (size >= drop.maxSize - 1) {
      if (drop.receding) drops[i] = newDrop();
      else {
        drops[i].receding = true;
        drops[i].start = now;
      }
      continue;
    }

    int start = drop.center - size;
    int end = drop.center + size;
    for (int led = start; led <= end; led++) {
      int index = transform(led);
      if (drop.receding) {
        if (leds[index] == drop.color) leds[index] = CRGB::Black; //don't erase other drops
      }
      else leds[index] = drop.color;
    }
  }
  FastLED.show();
}