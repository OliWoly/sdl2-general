#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include "../include/player.h"
#include "../include/Collision.h"
#include <iostream>
#include <math.h>

using namespace std;

// Constructor
// Controls isntance variables and default values when calling the function.
// When assigning new instance variables which are determined on
// construction, must change the constructor call in the header file too.
Player::Player(int x, int y, int w, int h, float speed, float* td, int* mouseXG, int* mousYG, int* mouseXL, int* mouseYL, float mouseModX, float mouseModY){
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->speed = speed;
        this->td = td;

        this->mouseXG = mouseXG;
        this->mouseYG = mouseYG;
        this->mouseXL = mouseXL;
        this->mouseYL = mouseYL;
        this->mouseModX = mouseModX;
        this->mouseModY = mouseModY;
    }

void Player::draw(SDL_Renderer* renderer){
    SDL_Rect rect = {(int)x, (int)y, (int)w, (int)h};    
    SDL_SetRenderDrawColor(renderer, colour[0], colour[1], colour[2], colour[3]);
    SDL_RenderFillRect(renderer, &rect);
}

void Player::moveToMouse(float stepSize = 0){
    float centreX = (float)x + ((float)w/2);
    float centreY = (float)y + ((float)h/2);
    // Angle in radians
    float angle = atan2((float)(*mouseYL * this->mouseModY) - centreY, (float)(*mouseXL * this->mouseModX) - centreX);

    // Only move if the mouse is a threshold distance away from the player.
    // Makes sure to not cause jankiness.
    // If confused, set "threshold" to 0.
    if (!Collision::collideTwoPoints(centreX, centreY, (float)*mouseXL, (float)*mouseYL, 2)){
    x += cos(angle) * speed * *td;
    y += sin(angle) * speed * *td;
    }
    // Only move required distance to reach destination.
    // Avoid too big movements and floors them to distance between points.
    else{
        // Just move to mouse
        x = *this->mouseXL;
        y = *this->mouseYL;
    }
}

void Player::stepRight(float stepSize = 0){
    if (stepSize == 0){
        stepSize = getSpeed();
    }
    x += (stepSize * *td);
}

void Player::stepLeft(float stepSize = 0){
    if (stepSize == 0){
        stepSize = getSpeed();
    }
    x -= (stepSize * *td);
}

void Player::stepUp(float stepSize = 0){
    if (stepSize == 0){
        stepSize = getSpeed();
    }
    y -= (stepSize * *td);
}

void Player::stepDown(float stepSize = 0){
    if (stepSize == 0){
        stepSize = getSpeed();
    }
    y += (stepSize * *td);
}

void Player::setX(int newx){
    x = newx;
}

void Player::setY(int newy){
    y = newy;
}

void Player::setTD(float newTD){
    *td = newTD;
}

void Player::setColour(int r, int g, int b, int a){
    colour[0] = r;
    colour[1] = g;
    colour[2] = b;
    colour[3] = a;
}

int Player::getX() {
    return x;
}

int Player::getY() {
    return y;
}

int Player::getW() {
    return w;
}

int Player::getH() {
    return h;
}

float Player::getSpeed() {
    return speed;
}

int* Player::getColour(){
    return colour;
}

float Player::getMouseXL(){
    return (float)*mouseXL; 
}

float Player::getMouseYL(){
    return (float)*mouseYL; 
}

void Player::displayCoordinates() {
    std::cout << "Player coordinates: (" << x << ", " << y << ")" << std::endl;
}

void Player::displayTimeDelta(){
    cout << *td << endl;
}

void Player::displayColour(){
    std::cout << colour << std::endl;
}

void Player::displayMouseCoordinates(){
    std::cout << *mouseXL << ", " << *mouseYL << std::endl;
}