#include <SDL.h>
#include "../include/Entity.h"


// Constructor
Entity::Entity(float startX, float startY, float startW, float startH, float* startTD){
    this->x = startX;
    this->y = startY;
    this->w = startW;
    this->h = startH;
    this->td = startTD;
    this->setColour(chooseRandomColour());
}

void Entity::draw(SDL_Renderer* renderer){
    // Pass through as pointers.
    SDL_Rect rect = {(int)x, (int)y, (int)w, (int)h};    
    SDL_SetRenderDrawColor(renderer, colour[0], colour[1], colour[2], colour[3]);
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

int* Entity::chooseRandomColour(){
    int* rcolour = new int[4];
    rcolour[0] = rand() % 256;
    rcolour[1] = rand() % 256;
    rcolour[2] = rand() % 256;
    rcolour[3] = 255;
    return rcolour;
}

void Entity::setColour(int* newColour){
    this->colour[0] = newColour[0];
    this->colour[1] = newColour[1];
    this->colour[2] = newColour[2];
    this->colour[3] = newColour[3];
}
