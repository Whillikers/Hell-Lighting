#include "potentiometer.h"

/**
 * Single-pin potentiometer constructor.
 *
 * Sets up analog pin and potentiometer internals.
 *
 * @param analogPin The pin associated to this potentiometer
 */
Potentiometer::Potentiometer(int analogPin) {
    _pin = analogPin;
}

/**
 * Get the potentiometer's raw reading.
 *
 * The analog reading will be an integer between pot_analog_min (0) and
 * pot_analog_max (1023).
 *
 * @return The angle as a value between pot_analog_min and pot_analog_max
 */
int Potentiometer::getAngleAnalog() {
    return analogRead(_pin);
}

/**
 * Get the potentiometer's reading as an 8-bit value.
 *
 * @return The angle as an integer value between 0 and UINT8_MAX (256).
 */
uint8_t Potentiometer::getAngle8() {
    return getAngleAnalog() >> 2;
}

/**
 * Get the potentiometer's reading as a 16-bit value.
 *
 * @return The angle as an integer value between 0 and UINT16_MAX (65536).
 */
uint8_t Potentiometer::getAngle16() {
    return getAngleAnalog() << 6;
}

/**
 * Get the potentiometer's angle as a value between 0 and 1.
 *
 * 0 is the potentiometer's most negative value (typically rotated all the
 * way counterclockwise) and 1 is the most positive value (typically
 * rotated all the way clockwise).
 *
 * @return The angle as a value between 0 and 1
 */
float Potentiometer::getAngleProportional() {
    return map(getAngleAnalog(), pot_analog_min, pot_analog_max, 0.0, 1.0);
}

/**
 * Get the potentiometer's angle as a degree measure.
 *
 * 0 is the potentiometer's most negative value (typically rotated all the
 * way counterclockwise) and 360 is the most positive value (typically
 * rotated all the way clockwise).
 *
 * @return The angle as a value between 0 and 360
 */
float Potentiometer::getAngleDegrees() {
    return getAngleProportional() * 360.0;
}
