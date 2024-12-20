#include <SDL.h>
#include "../include/Entity.h"


// Constructor
Entity::Entity(float startX, float startY, float startW, float startH, float* startTD){
    x = startX;
    y = startY;
    w = startW;
    h = startH;
    td = startTD;
}

void Entity::draw(SDL_Renderer* renderer){
    // Pass through as pointers.
    SDL_Rect rect = {(int)x, (int)y, (int)w, (int)h};    
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &rect);
}

float Entity::getX() {
    return x;
}

float Entity::getY() {
    return y;
}

float Entity::getW() {
    return w;
}

float Entity::getH() {
    return h;
}
