#ifndef PARTICLE_H // essentially pragma once.
#define PARTICLE_H
#include <array>
#include <SDL2/SDL.h>

class Particle {
private:
    float x;
    float y;
    float size;
    std::array<int, 4> colour;
    float originX;
    float originY;

    float friction;
    float speed;
    float gravity;

    bool alive;
    float lifetime;
    std::chrono::high_resolution_clock::time_point birth;
    float age;

public:
    Particle() = default;
    Particle(float x, float y, float size, const std::array<int, 4>& colour, float originX, float originY);
    void draw(SDL_Renderer* renderer);
    void update(float* td);
    void checkLifetime();
    void moveExplode(float* td);
    void applyFriction(float* td);
    float getX();
    bool getStatus();
    void applyGravity(float* td);
    void applyAlphaChange();

    void displayCoordinates();

};

#endif