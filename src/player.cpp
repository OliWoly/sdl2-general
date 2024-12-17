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



// Getter for X
int Player::getX() const {
    return x;
}

// Getter for Y
int Player::getY() const {
    return y;
}

// Method to display coordinates
void Player::displayCoordinates() const {
    std::cout << "Player coordinates: (" << x << ", " << y << ")" << std::endl;
}