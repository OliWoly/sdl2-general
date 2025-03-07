#ifndef PLAYER_H // essetntally pragma once.
#define PLAYER_H
#include <SDL2/SDL.h>


class Player {
private:
    float x;  // X-coordinate
    float y;  // Y-coordinate
    float w;  // Width
    float h;  // Height
    float speed;
    float* td;  // Must dereference with * to get time delta.
                // As in float td = *td.
    int colour[4] = {255, 255, 255, 255};

    int* mouseXG;
    int* mouseYG;
    int* mouseXL;
    int* mouseYL;

    float mouseModX;
    float mouseModY;

public:
    // Constructor
    // Must change if adding new instance variables.
    Player() = default;
    Player(
        int startX, 
        int startY, 
        int startW, 
        int startH,
        float startSpeed,
        float* td,

        int* mousePosXGlobal,
        int* mousePosYGlobal,
        int* mousePosXLocal,
        int* mousePosYLocal,

        float mouseModX,
        float mouseModY
        );

    // Modifiers
    void draw(SDL_Renderer* renderer);

    void moveToMouse(float stepSize);
    void stepRight(float stepSize);
    void stepLeft(float stepSize);
    void stepUp(float stepSize);
    void stepDown(float stepSize);

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
    float getSpeed();
    int* getColour();
    float getMouseXL();
    float getMouseYL();

    // Method to display coordinates
    void displayCoordinates();
    void displayTimeDelta();
    void displayColour();
    void displayMouseCoordinates();
};

#endif // PLAYER_H
