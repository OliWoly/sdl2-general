#ifndef PLAYER_H // essetntally pragma once.
#define PLAYER_H

class Player {
private:
    int x;  // X-coordinate
    int y;  // Y-coordinate
    int w;  // Width
    int h;  // Height
    int speed;

public:
    // Constructor
    // Must change if adding new instance variables.
    Player(
        int startX = 0, 
        int startY = 0, 
        int startW = 0, 
        int startH = 0,
        int startSpeed = 5);

    // Modifiers
    void stepRight(int stepSize);
    void stepLeft(int stepSize);
    void stepUp(int stepSize);
    void stepDown(int stepSize);

    // Setters
    void setX(int newx);
    void setY(int newx);

    // Getters
    int getX();
    int getY();
    int getW();
    int getH();
    int getSpeed();

    // Method to display coordinates
    void displayCoordinates();
};

#endif // PLAYER_H
