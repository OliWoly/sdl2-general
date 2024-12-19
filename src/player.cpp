#include <SDL.h>
#include <SDL_render.h>
#include "../include/player.h"
#include <iostream>
#include <math.h>

using namespace std;

// Constructor
// Controls isntance variables and default values when calling the function.
// When assigning new instance variables which are determined on
// construction, must change the constructor call in the header file too.
Player::Player(
    int startX, 
    int startY, 
    int startW, 
    int startH,
    float startSpeed,
    float* initialTD,
    
    int* mousePosXGlobal,
    int* mousePosYGlobal,
    int* mousePosXLocal,
    int* mousePosYLocal
    ) 
    {
        x = startX;
        y = startY;
        w = startW;
        h = startH;
        speed = startSpeed;
        td = initialTD;

        mouseXG = mousePosXGlobal;
        mouseYG = mousePosYGlobal;
        mouseXL = mousePosXLocal;
        mouseYL = mousePosYLocal;
    }

void Player::draw(SDL_Renderer* renderer){
    SDL_Rect rect = {*&x, *&y, *&w, *&h};    
    SDL_SetRenderDrawColor(renderer, colour[0], colour[1], colour[2], colour[3]);
    SDL_RenderFillRect(renderer, &rect);
}

void Player::moveToMouse(int stepSize = 0){
    float centreX = (float)x + ((float)w/2);
    float centreY = (float)y + ((float)h/2);
    // Angle in radians
    float angle = atan2((float)*mouseYL - centreY, (float)*mouseXL - centreX);
    
    x += cos(angle) * speed * *td;
    y += sin(angle) * speed * *td;

    //std::cout << angle * 180 / 3.1415 << std::endl;
}

void Player::stepRight(int stepSize = 0){
    if (stepSize == 0){
        stepSize = getSpeed();
    }
    float realtd = *td;
    x += (stepSize * realtd);
}

void Player::stepLeft(int stepSize = 0){
    if (stepSize == 0){
        stepSize = getSpeed();
    }

    float realtd = *td;
    x -= (stepSize * realtd);
}

void Player::stepUp(int stepSize = 0){
    if (stepSize == 0){
        stepSize = getSpeed();
    }

    float realtd = *td;
    y -= (stepSize * realtd);
}

void Player::stepDown(int stepSize = 0){
    if (stepSize == 0){
        stepSize = getSpeed();
    }

    float realtd = *td;
    y += (stepSize * realtd);
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

int Player::getSpeed() {
    return speed;
}

int* Player::getColour(){
    return colour;
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