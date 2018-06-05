#include "board.h"

/**
 * Get a given button from this board, or a dummy if none is available.
 *
 * @param which The button to get, numbered from 0
 * @return the button.
 */
Button Board::getButton(int which) {
    if (which < this->_nButtons) {
        return this->_buttons[which];
    }
    return ButtonDummy();
}

/**
 * Get a given button from this board, or fail if none is available.
 *
 * @param which The button to get, numbered from 0
 * @return the button.
 */
Button Board::getButtonStrict(int which) {
    assert(which < this->_nButtons);
    return this->_buttons[which];
}

/**
 * Get a given potentiometer from this board, or a dummy if none is available.
 *
 * @param which The potentiometer to get, numbered from 0
 * @return the potentiometer.
 */
Potentiometer Board::getPotentiometer(int which) {
    if (which < this->_nPotentiometers) {
        return this->_potentiometers[which];
    }
    return PotentiometerDummy();
}

/**
 * Get a given potentiometer from this board, or fail if none is available.
 *
 * @param which The potentiometer to get, numbered from 0
 * @return the potentiometer.
 */
Potentiometer Board::getPotentiometerStrict(int which) {
    assert(which < this->_nPotentiometers);
    return this->_potentiometers[which];
}
