#include "pattern_race_2.h"

void Pattern_Race_2::init() {
    clearLEDs();
    FastLED.setBrightness(BRIGHTNESS_MAX);
    raceDist = min(abs(LEFT_END - LEFT_START), abs(RIGHT_END - RIGHT_START));

    flashcount = 0;

    red = 0;
    blue = 0;
    redSpeed = random(minSpeed, maxSpeed);
    blueSpeed = random(minSpeed, maxSpeed);
    for (int i = 0; i < shifts; i++) {
        redSpeeds[i] = random(minSpeed, maxSpeed);
        blueSpeeds[i] = random(minSpeed, maxSpeed);
        redSpeedLocations[i] = random(0, raceDist);
        blueSpeedLocations[i] = random(0, raceDist);
    }
}

void Pattern_Race_2::loop() {
    switch (state) {
        case countdown:

            // flash countdown
            if (flashcount == countdownFlashes) {
                state = race;
                flashcount = 0;
            } else {
                for (int i = LEFT_START; i < LEFT_END; i++) {
                    leds[transform(i)] = CRGB::Red;
                }
                for (int i = RIGHT_START; i > RIGHT_END; i--) {
                    leds[transform(i)] = CRGB::Blue;
                }
                FastLED.show();

                delay(500);

                for (int i = LEFT_START; i < LEFT_END; i++) {
                    leds[transform(i)] = CRGB::Black;
                }
                for (int i = RIGHT_START; i > RIGHT_END; i--) {
                    leds[transform(i)] = CRGB::Black;
                }
                FastLED.show();

                delay(500);

                flashcount++;
            }

            break;

        case race:

            if (abs(red) >= raceDist || abs(blue) >= raceDist) {
                state = finish;
            } else {
                // update positions
                red += ((float) redSpeed) / ((float) stp);
                blue += ((float) blueSpeed) / ((float) stp);

                float maxRed = 0;
                float maxBlue = 0;
                for (int j = 0; j < shifts; j++) {
                    if (red > redSpeedLocations[j] && redSpeedLocations[j] > maxRed) {
                        redSpeed = redSpeeds[j];
                        maxRed = redSpeedLocations[j];
                    }
                    if (blue > blueSpeedLocations[j] && blueSpeedLocations[j] > maxBlue) {
                        blueSpeed = blueSpeeds[j];
                        maxBlue = blueSpeedLocations[j];
                    }
                }

                leds[transform(LEFT_START + (int) red)] = CRGB::Red;
                leds[transform(RIGHT_START - (int) blue)] = CRGB::Blue;
                FastLED.show();
                delay(stp);
            }

            break;

        case finish:
            if (red > blue) {
                for (int i = LEFT_START; i < LEFT_END; i++) {
                    leds[transform(i)] = CRGB::Red;
                }
                FastLED.show();
                delay(500);
                for (int i = LEFT_START; i < LEFT_END; i++) {
                    leds[transform(i)] = CRGB::Black;
                }
                FastLED.show();
                delay(500);
            } else {
                for (int i = RIGHT_START; i > RIGHT_END; i--) {
                    leds[transform(i)] = CRGB::Blue;
                }
                FastLED.show();
                delay(500);
                for (int i = RIGHT_START; i > RIGHT_END; i--) {
                    leds[transform(i)] = CRGB::Black;
                }
                FastLED.show();
                delay(500);
            }

            break;
    }
}

