#ifndef ENTITY_H // essetntally pragma once.
#define ENTITY_H
#include <SDL.h>
#include <SDL2/SDL_render.h>

class Entity {
public:
    int x;
    int y;
    int w;
    int h;
    float* td;

    // Functions:
    // Class Methods

    Entity(int startX, int startY, int startW, int startH, float* startTD);
    void draw(SDL_Renderer* renderer);
    int getX();
    int getY();
    int getW();
    int getH();
};


#endif