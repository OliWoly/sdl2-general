#include <iostream>
#include <math.h>
#include <SDL.h>
#include <SDL2/SDL_hints.h>
#include "../include/player.h"
#include "../include/Entity.h"
#include "../include/Collision.h"

Collision::Collision(){
    modifier = 0;
}

bool Collision::collideTwoPoints(float p1x, float p1y, float p2x, float p2y, float threshold){
    // returns true if the distance between two points is less than the threshold.
    if (Collision::distanceBetweenPoints(p1x, p1y, p2x, p2y) < threshold){
        return true;
    }
    else{
        return false;
    }
}

bool Collision::collidePlayer_w_Entity(Player* player, Entity* entity){
    // Pure check.
    if (player->getX() < entity->getX() + entity->getW() &&
        player->getX() + player->getW() > entity->getX() &&
        player->getY() < entity->getY() + entity->getH() &&
        player->getY() + player->getH() > entity->getY()) {
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

float Collision::distanceBetweenPoints(float p1x, float p1y, float p2x, float p2y){
    // Distance forumula
    // https://www.google.com/search?client=firefox-b-d&q=distance+forumla
    float distance = sqrt(pow(p2x-p1x, 2) + pow(p2y-p1y, 2));
    return distance;
}

void Collision::displayModifier(){
    std::cout << modifier << std::endl;
}