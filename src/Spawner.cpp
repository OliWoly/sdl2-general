#include <array>
#include <vector>
#include <SDL.h>
#include "../include/Spawner.h"
#include "../include/Entity.h"

Spawner::Spawner(float* td, int* screenWidth, int*screenHeight){
    this->td = td;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}

void Spawner::spawnEnemies(std::vector<Entity> &entities, int numberOfEnemiesToSpawn){
    // Spawn desired number of enemies
    for (int i = 0; i < numberOfEnemiesToSpawn; i++){
        std::array<float, 4> entargs = Spawner::getRandomEntityConstructorArgs();
        entities.push_back(Entity(entargs[0], entargs[1], entargs[2], entargs[3], this->td));
    }
};

std::array<float, 4> Spawner::getRandomEntityConstructorArgs(){
    std::array<float, 4> args;
    // [0] = x
    // [1] = y
    // [2] = w
    // [3] = h

    // First figure out the width and height to properly 
    // asses the initial position of the entities.

    // rand() is random number generator
    args[2] = rand() % 50;
    args[3] = rand() % 50;

    // now position
    args[0] = rand() % (int)(*this->screenWidth - args[2]);
    args[1] = rand() % (int)(*this->screenHeight - args[3]);

    return args;
}