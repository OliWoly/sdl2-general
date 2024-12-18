#include "../include/InputHandler.h"
#include "../include/player.h"
#include <iostream>

using namespace std;

// Emptty constructor. All default values at false.
InputHandler::InputHandler(){}

void InputHandler::asses(Player *player){
    // Check through all key checking functions.
    check_w_key(player);
}

// What to do when W key is pressed.
void InputHandler::check_w_key(Player *player){
    if (w_key == true){
        player->stepUp(player->getSpeed());
    }
}


