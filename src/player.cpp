#include <SDL.h>
#include <SDL_render.h>
#include "../include/player.h"
#include <iostream>

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
    float* initialTD
    ) 
    : 
    x(startX), 
    y(startY), 
    w(startW), 
    h(startH),
    speed(startSpeed),
    td(initialTD)
    {}

void Player::draw(SDL_Renderer* renderer){
    SDL_Rect rect = {x, y, w, h};    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
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

void Player::setY(int newx){
    x = newx;
}

void Player::setTD(float newTD){
    *td = newTD;
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

// Method to display coordinates
void Player::displayCoordinates() {
    std::cout << "Player coordinates: (" << x << ", " << y << ")" << std::endl;
}

void Player::displayTimeDelta(){
    cout << *td << endl;
}