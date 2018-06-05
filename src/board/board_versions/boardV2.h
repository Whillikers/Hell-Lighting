#pragma once
#include "../board.h"

class BoardV2 : public Board {
public:
    BoardV2() : Board(
       0, {},                       // Button settings
       1, {new Potentiometer(A0)}   // Pot settings
    ) {}
};
