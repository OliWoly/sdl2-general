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
    
    bool f3_key = false;
    bool esc_key = false;
    bool space_key = false;

    // FUNCTIONS:
    // Constructor
    InputHandler();

    // Methods
    void asses(Player *player);
    void check_w_key(Player *player);
    void check_a_key(Player *player);
    void check_s_key(Player *player);
    void check_d_key(Player *player);
    void check_f3_key(Player *player);
    void check_space_key(Player *player);

    void displayAllCurrentStates();
};


#endif