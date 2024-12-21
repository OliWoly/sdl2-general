#include "../include/InputHandler.h"
#include "../include/player.h"
#include "../include/Entity.h"
#include "../include/Spawner.h"
#include <iostream>
#include <vector>

// Emptty constructor. All default values at false.
InputHandler::InputHandler(){}

void InputHandler::asses(Player *player, std::vector<Entity> &entities, Spawner *spawner){
    // Check through all key checking functions.
    check_w_key(player);
    check_a_key(player);
    check_s_key(player);
    check_d_key(player);

    check_e_key(*&player, entities, *&spawner);

    check_space_key(player);
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

void InputHandler::check_space_key(Player *player){
    if (space_key == true){
        player->moveToMouse(player->getSpeed());
    }
}

void InputHandler::check_e_key(Player *player, std::vector<Entity> &entities, Spawner *spawner){
    if (e_key == true){
        spawner->spawnEnemies(entities, 1);
    }
}

void InputHandler::displayAllCurrentStates(){
    std::cout << "W: " << w_key << std::endl;
    std::cout << "A: " << a_key << std::endl;
    std::cout << "S: " << s_key << std::endl;
    std::cout << "D: " << d_key << std::endl;
}


