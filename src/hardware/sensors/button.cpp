#include "button.h"

/// HARDWARE BUTTONS ///
/**
 * Default button constructor.
 *
 * @param pin The pin associated to this button
 */
Button::Button(int pin) {
    pinMode(pin, INPUT);
    _pin = pin;
}


/**
 * Get whether the button is currently being pressed.
 *
 * @return whether the button is pressed currently.
 */
bool Button::isPressed() {
    return (digitalRead(_pin) == HIGH);
}


/// DUMMY BUTTON ///
/**
 * @return false.
 */
bool ButtonDummy::isPressed() {
    return false;
}
