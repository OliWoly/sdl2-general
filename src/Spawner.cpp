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
    // + 20 at the end sets the minimum.
    // maximum is minimum + random variance.
    args[2] = (rand() % 30) + 20;
    args[3] = (rand() % 30) + 20;

    // now position
    args[0] = rand() % (int)(*this->screenWidth - args[2]);
    args[1] = rand() % (int)(*this->screenHeight - args[3]);

    return args;
}

void Spawner::removeEnemies(std::vector<Entity>& entities, std::vector<int> indexes) {
    // Sort indexes in ascending order
    std::sort(indexes.begin(), indexes.end());

    // Remove elements starting from the back
    for (auto it = indexes.rbegin(); it != indexes.rend(); ++it) {
        int index = *it;
        if (index >= 0 && index < entities.size()) { // Ensure index is valid
            entities.erase(entities.begin() + index);
        }
    }
}