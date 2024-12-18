#include <iostream>
#include <SDL.h>
#include <SDL2/SDL_hints.h>
#include "../include/player.h"
#include "../include/Entity.h"
#include "../include/Collision.h"

Collision::Collision(){
    modifier = 1;
}

bool Collision::collidePlayer_w_Entity(Player* player, Entity* entity){
    // Abstraction
    int p_tl = player->getX();
    int p_tr = player->getX() + player->getW();
    int p_br = player->getY() + player->getW();
    int p_bl = player->getY() + player->getH();

    int e_tl = entity->getX();
    int e_tr = entity->getX() + entity->getW();
    int e_br = entity->getY() + entity->getW();
    int e_bl = entity->getY() + entity->getH();


    if (player->getX() < entity->getX() + entity->getW() &&
        player->getX() + player->getW() > entity->getX() &&
        player->getY() < entity->getY() + entity->getH() &&
        player->getY() + player->getH() > entity->getY()) {
        
        std::cout << "colliding" << std::endl;
        return true;
        }
    else {
        return false;
    }
}

void Collision::collidePlayerBoundariesScreen(Player* player, int maxWidth, int maxHeight){
    int maxRight = maxWidth - player->getW();
    int maxDown = maxHeight - player->getH();
    
    // if too far left.
    if (player->getX() < 0){
        player->setX(0);
    }
    // if too far right.
    if (player->getX() > maxRight){
        player->setX(maxRight);
    }
    // if too far up.
    if (player->getY() < 0){
        player->setY(0);
    }
    // if too far down.
    if (player->getY() > maxDown){
        player->setY(maxDown);
    }
}