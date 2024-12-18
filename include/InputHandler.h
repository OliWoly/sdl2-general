#ifndef INPUTHANDLER_H // essetntally pragma once.
#define INPUTHANDLER_H

#include "../include/player.h"

class InputHandler {
public:
    // INSTANCE VARIABLES
    bool w_key = false;
    bool a_key = false;
    bool s_key = false;
    bool d_key = false;
    
    bool esc_key = false;

    // FUNCTIONS:
    // Constructor
    InputHandler();

    // Methods
    void asses(Player *player);
    void check_w_key(Player *player);
};


#endif