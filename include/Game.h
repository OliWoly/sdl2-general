#ifndef GAME_H // essetntally pragma once.
#define GAME_H
#include <SDL.h>
#include "../include/player.h"
#include "../include/InputHandler.h"
#include "../include/Entity.h"
#include "../include/Spawner.h"

class Game{
private:
    bool running;
    int SCR_W;
    int SCR_H;

    SDL_Window* window;
    SDL_Renderer* renderer;

    Player p;
    Spawner spawner;
    InputHandler inputHandler;
    std::vector<Entity> entities;

    SDL_Event event;

    // Time Delta used for movement calculation.
    // Framerate independancy.
    // Always pass through functions other class constructors as a pointer.
    float td;
    int xMouse, yMouse;
    int xMouseG, yMouseG;
    float framerate;


    void closeGameWithOS(SDL_Event* event);
    void handleMouse(SDL_Event* event);
    void handleKeybaord(SDL_Event* event);
    void handleKeybaord_KeyDown(SDL_Event* event);
    void handleKeybaord_KeyUp(SDL_Event* event);
    

public:
    Game(int SCR_W, int SCR_H);
    void initEngine();
    void initClasses();
    void update();
    void gameLogic();
    void gameLogic_Collision();

    void inputs();

    void drawing();

    int getScreenWidth();
    int getScreenHeight();



};















#endif