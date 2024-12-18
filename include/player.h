#ifndef PLAYER_H // essetntally pragma once.
#define PLAYER_H
#include <SDL.h>


class Player {
private:
    int x;  // X-coordinate
    int y;  // Y-coordinate
    int w;  // Width
    int h;  // Height
    float speed;
    float* td;  // Must dereference with * to get time delta.
                // As in float td = *td.
    int colour[4] = {255, 255, 255, 255};

public:
    // Constructor
    // Must change if adding new instance variables.
    Player(
        int startX = 0, 
        int startY = 0, 
        int startW = 0, 
        int startH = 0,
        float startSpeed = 0.5,
        float* td = 0
        );

    // Modifiers
    void draw(SDL_Renderer* renderer);

    void stepRight(int stepSize);
    void stepLeft(int stepSize);
    void stepUp(int stepSize);
    void stepDown(int stepSize);

    // Setters
    void setX(int newx);
    void setY(int newx);
    void setTD(float newTD);
    void setColour(int r, int g, int b, int a);

    // Getters
    int getX();
    int getY();
    int getW();
    int getH();
    int getSpeed();
    int* getColour();

    // Method to display coordinates
    void displayCoordinates();
    void displayTimeDelta();
    void displayColour();
};

#endif // PLAYER_H
