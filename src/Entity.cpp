#include <SDL.h>
#include "../include/Entity.h"


// Constructor
Entity::Entity(int startX, int startY, int startW, int startH, float* startTD){
    x = startX;
    y = startY;
    w = startW;
    h = startH;
    td = startTD;
}

void Entity::draw(SDL_Renderer* renderer){
    // Pass through as pointers.
    SDL_Rect rect = {*&x, *&y, *&w, *&h};    
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &rect);
}

int Entity::getX() {
    return x;
}

int Entity::getY() {
    return y;
}

int Entity::getW() {
    return w;
}

int Entity::getH() {
    return h;
}
