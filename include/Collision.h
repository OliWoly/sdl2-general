#ifndef COLLISION_H // essetntally pragma once.
#define COLLISION_H
#include <SDL.h>
#include "../include/player.h"
#include "../include/Entity.h"

class Collision{


public:
    float modifier;
    Collision();

    bool collidePlayer_w_Entity(Player* player, Entity* entity);
    void collidePlayerBoundariesScreen(Player* player, int maxWidth, int maxHeight);
};



#endif