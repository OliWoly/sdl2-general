#ifndef SPAWNER_H // essentially pragma once.
#define SPAWNER_H
#include <vector>
#include "../include/Entity.h"
#include <SDL.h>
#include <SDL2/SDL_render.h>

class Spawner{
private:
    float* td;
    int* screenWidth;
    int* screenHeight;

public:

    Spawner(float* td, int* screenWidth, int* screenHeight);
    void spawnEnemies(std::vector<Entity> &enemies, int numberOfEnemiesToSpawn);
    std::array<float, 4> getRandomEntityConstructorArgs();
};

#endif