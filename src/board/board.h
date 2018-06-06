#pragma once
#include "../config/hardware.h"
#include "../hardware/sensors/potentiometer.h"
#include "../hardware/sensors/button.h"
#include <assert.h>

/**
 * Base class for boards, which have certain configurations of
 * hardware, sensors, etc.
 */
class Board {
public:
    Board(int nButtons = 0, Button buttons[] = {},
          int nPotentiometers = 0, Potentiometer potentiometers[] = {}) :
              _nButtons(nButtons), _nPotentiometers(nPotentiometers),
              _buttons(buttons), _potentiometers(potentiometers) {}

    const int _nButtons;
    const int _nPotentiometers;

    Button getButton(int which);
    Button getButtonStrict(int which);
    Potentiometer getPotentiometer(int which);
    Potentiometer getPotentiometerStrict(int which);

protected:
    Button* _buttons;
    Potentiometer* _potentiometers;
};
