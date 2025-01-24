#ifndef SPAWNER_H // essentially pragma once.
#define SPAWNER_H
#include <vector>
#include "../include/Entity.h"
#include "../include/Particle.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>

class Spawner{
private:
    float* td;
    int* screenWidth;
    int* screenHeight;

public:
    Spawner() = default;
    Spawner(float* td, int* screenWidth, int* screenHeight);
    void spawnEnemies(std::vector<Entity> &enemies, int numberOfEnemiesToSpawn);
    std::array<float, 4> getRandomEntityConstructorArgs();
    void removeEnemies(std::vector<Entity> &entity, std::vector<int> indexes);
    void explodeEnemy(Entity* entity, std::vector<Particle> &particles, int particleSize);
    void spawnParticle(std::vector<Particle>& particles, int x, int y, int size, const std::array<int, 4>& colour, float originX, float originY);
    void removeParticles(std::vector<Particle>& particles, std::vector<int> indexes);

    void displayInstanceVariables();
};

#endif