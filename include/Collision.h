#ifndef COLLISION_H // essetntally pragma once.
#define COLLISION_H
#include <SDL2/SDL.h>
#include "../include/player.h"
#include "../include/Entity.h"

class Collision{


public:
    float modifier;
    Collision();
    static float distanceBetweenPoints(float p1x, float p1y, float p2x, float p2y);
    static bool collideTwoPoints(float p1x, float p1y, float p2x, float p2y, float threshold);
    static bool collidePlayer_w_Entity(Player* player, Entity* entity);
    static void collidePlayerBoundariesScreen(Player* player, int maxWidth, int maxHeight);
    void displayModifier();
};



#endif