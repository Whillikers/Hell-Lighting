#include "pattern_color.h"

void Pattern_Color::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);

    Serial.println("Color pattern finished init");
}

void Pattern_Color::loop() {
    Serial.println("Color pattern loop frame");

    col = CHSV(map(analogRead(PIN_POT), 0, POT_MAX, 0, 255), 255, 255);
    for (int i = 0; i < NUM_LEDS_TOTAL; i++) {
        leds[transform(i)] = col;
    }

    FastLED.show();
    // delay(1000); //TODO: Change to 10 or remove
}
