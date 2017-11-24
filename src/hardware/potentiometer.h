# pragma once

#include "../common.h"

/**
 * @ingroup hardware
 *
 * Generic hardware potentiometer.
 *
 * Acts as a plug-and-play single-pin potentiometer and also a superclass
 * for specific types of potentiometers (with different ranges, etc).
 */
class Potentiometer {
public:
    Potentiometer(int analogPin);

    float getAngleProportional();
    float getAngleDegrees();


protected:
    /**
     * Minimum value possible to read for an analog potentiometer.
     */
    static const int pot_analog_min = 0;

    /**
     * Maximum value possible to read for an analog potentiometer.
     */
    static const int pot_analog_max = 1023;


private:
    int _pin;

    int getAngleAnalog();
};

