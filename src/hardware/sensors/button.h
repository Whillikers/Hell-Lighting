#pragma once

#include "../../common.h"

/**
 * @ingroup hardware
 *
 * Generic digital hardware button; not debounced.
 */
class Button {
public:
    Button(int pin);
    bool isPressed();

protected:
    Button() = default;  // For dummy buttons; do not use!
    int _pin;
};


/**
 * @ingroup hardware
 *
 * Dummy button that never registers pressed.
 */
class ButtonDummy : public Button {
public:
    ButtonDummy() = default;
    bool isPressed();
};
