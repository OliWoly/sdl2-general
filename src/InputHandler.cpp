#include "../include/InputHandler.h"
#include "../include/player.h"
#include <iostream>

using namespace std;

// Emptty constructor. All default values at false.
InputHandler::InputHandler(){}

void InputHandler::asses(Player *player){
    // Check through all key checking functions.
    check_w_key(player);
    check_a_key(player);
    check_s_key(player);
    check_d_key(player);
}

// What to do when W key is pressed.
void InputHandler::check_w_key(Player *player){
    if (w_key == true){
        player->stepUp(player->getSpeed());
    }
}

// What to do when A key is pressed.
void InputHandler::check_a_key(Player *player){
    if (a_key == true){
        player->stepLeft(player->getSpeed());
    }
}

// What to do when S key is pressed.
void InputHandler::check_s_key(Player *player){
    if (s_key == true){
        player->stepDown(player->getSpeed());
    }
}

// What to do when D key is pressed.
void InputHandler::check_d_key(Player *player){
    if (d_key == true){
        player->stepRight(player->getSpeed());
    }
}

void InputHandler::check_f3_key(Player *player){
    if (f3_key == true){
        displayAllCurrentStates();
    }
}

void InputHandler::displayAllCurrentStates(){
    cout << "W: " << w_key << endl;
    cout << "A: " << a_key << endl;
    cout << "S: " << s_key << endl;
    cout << "D: " << d_key << endl;
}


