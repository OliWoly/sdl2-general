#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>
#include <cmath>
#include <cstdlib>
#include "../include/Particle.h"

const float INITIAL_GRAVITY = 0.01;

Particle::Particle(float x, float y, float size, const std::array<int, 4>& colour, float originX, float originY){
    this->x = x;
    this->y = y;
    this->size = size;
    this->colour = colour;
    this->originX = originX;
    this->originY = originY;
    

    
    this->speed = (std::sqrt(pow(this->x-this->originX, 2) + pow(this->y-this->originY, 2))/1000) * 10;
    this->friction = this->speed/600;
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

void Particle::checkLifetime(){
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - this->birth;
    if (duration.count() >= this->lifetime){
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

float Particle::getX(){
    return this->x;
}

bool Particle::getStatus(){
    return this->alive;
}

void Particle::displayCoordinates(){
    std::cout << "Position: " << this->x << ", " << this->y << std::endl;
}