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

    // Getter for X
    int getX() const;

    // Getter for Y
    int getY() const;

    // Method to display coordinates
    void displayCoordinates() const;
};

#endif // PLAYER_H
