#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>
#include <cmath>
#include <cstdlib>
#include "../include/Particle.h"

const float INITIAL_GRAVITY = 0.001;

Particle::Particle(float x, float y, float size, const std::array<int, 4>& colour, float originX, float originY){
    this->x = x;
    this->y = y;
    this->size = size;
    this->colour = colour;
    this->originX = originX;
    this->originY = originY;
    
    this->speed = 1;
    this->friction = 0.001;
    this->gravity = INITIAL_GRAVITY;

    this->alive = true;
    // Floor 10, Ceiling 20, Final: 1-2
    // Lifetime is in seconds;
    this->lifetime = ((float)(rand() % 1000) + 1000) / 1000;

    // Timestamp of creation.    
    this->birth = std::chrono::high_resolution_clock::now();
}

void Particle::draw(SDL_Renderer* renderer){
    SDL_Rect rect = {(int)this->x, (int)this->y, (int)this->size, (int)this->size};    
    SDL_SetRenderDrawColor(renderer, this->colour[0], this->colour[1], this->colour[2], this->colour[3]);
    SDL_RenderFillRect(renderer, &rect);
}

void Particle::update(float* td){
    this->checkLifetime();
    this->moveExplode(td);
    this->applyFriction(td);
    this->applyGravity(td);
    this->applyAlphaChange();
}

void Particle::checkLifetime(){
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - this->birth;
    this->age = duration.count();
    if (this->age >= this->lifetime){
        this->alive = false;
    }
    else{
        this->alive = true;
    }
}

void Particle::moveExplode(float* td) {
    // Calculate the angle from the origin
    float angle = atan2(this->y - this->originY, this->x - this->originX);
    // Move the particle outward in the direction of its angle
    this->x += cos(angle) * this->speed * *td;
    this->y += sin(angle) * this->speed * *td;
}

void Particle::applyFriction(float* td){
    this->speed -= this->friction * *td;
    if (this->speed < 0){
        this->speed = 0;
    }
}

void Particle::applyGravity(float* td){
    this->y += this->gravity * *td;
    this->gravity += INITIAL_GRAVITY/3 * *td;
}

void Particle::applyAlphaChange(){
    // must run after checkLifetime.
    float lifetimePercentage = this->age / this->lifetime * 100;
    float newAlpha = 255 - (float)255/100 * lifetimePercentage;

    // Value clipping.
    if (newAlpha > 255){
        newAlpha = 255;
    }
    if (newAlpha < 0){
        newAlpha = 0;
    }
    this->colour[3] = (int)newAlpha;
}

float Particle::getX(){
    return this->x;
}

bool Particle::getStatus(){
    return this->alive;
}

void Particle::displayCoordinates(){
    std::cout << "Position: " << this->x << ", " << this->y << std::endl;
}