#include "../include/player.h"
#include <iostream>



// Constructor
// Controls isntance variables and default values when calling the function.
// When assigning new instance variables which are determined on
// construction, must change the constructor call in the header file too.
Player::Player(
    int startX, 
    int startY, 
    int startW, 
    int startH,
    int startSpeed
    ) 
    : 
    x(startX), 
    y(startY), 
    w(startW), 
    h(startH),
    speed(startSpeed) 
    {}



void Player::stepRight(int stepSize = 0){
    if (stepSize == 0){
        stepSize = getSpeed();
    }

    x += stepSize;
}


void Player::stepLeft(int stepSize = 0){
    if (stepSize == 0){
        stepSize = getSpeed();
    }

    x -= stepSize;
}


void Player::stepUp(int stepSize = 0){
    if (stepSize == 0){
        stepSize = getSpeed();
    }

    y -= stepSize;
}


void Player::stepDown(int stepSize = 0){
    if (stepSize == 0){
        stepSize = getSpeed();
    }

    y += stepSize;
}

void Player::setX(int newx){
    x = newx;
}

void Player::setY(int newx){
    x = newx;
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