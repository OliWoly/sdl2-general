#ifndef ENTITY_H // essetntally pragma once.
#define ENTITY_H
#include <SDL.h>
#include <SDL2/SDL_render.h>

class Entity {
public:
    float x;
    float y;
    float w;
    float h;
    float* td;
    int colour [4] = {rand() % 256, rand() % 256, rand() % 256, 255};

    // Functions:
    // Class Methods

    Entity() = default;
    Entity(float startX, float startY, float startW, float startH, float* startTD);
    void draw(SDL_Renderer* renderer);
    float getX();
    float getY();
    float getW();
    float getH();

    void setColour(int* newColour);
    static int* chooseRandomColour();
};


#endif