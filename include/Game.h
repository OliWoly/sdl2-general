#ifndef GAME_H // essetntally pragma once.
#define GAME_H
#include <atomic>
#include <string>

#include <SDL2/SDL.h>
#include "../include/player.h"
#include "../include/InputHandler.h"
#include "../include/Entity.h"
#include "../include/Spawner.h"
#include "../include/Particle.h"

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
    std::vector<Particle> entityParticles;

    SDL_Event event;

    // Time Delta used for movement calculation.
    // Framerate independancy.
    // Always pass through functions other class constructors as a pointer.
    float td;
    std::atomic<float>* tdA; // Atomic.
    int xMouse, yMouse;
    int xMouseG, yMouseG;
    float framerate;


    void closeGameWithOS(SDL_Event* event);
    void handleMouse(SDL_Event* event);
    void handleKeybaord(SDL_Event* event);
    void handleKeybaord_KeyDown(SDL_Event* event);
    void handleKeybaord_KeyUp(SDL_Event* event);

    // Logical window size. (used for scaling).
    int L_SCR_W;
    int L_SCR_H;

    // Difference between logical and real window size as modifier
    // e.g 1.33x size diff.
    float windowLogicalSizeModifierDifferenceWidth;
    float windowLogicalSizeModifierDifferenceHeight;
    

public:
    Game(int SCR_W, int SCR_H);
    void initEngine();
    void initClasses();
    void update();
    void gameLogic();
    void gameLogic_Collision();
    void gameLogic_Movement();
    void particleMovement();

    void inputs();

    void drawing();

    int getScreenWidth();
    int getScreenHeight();

    void printValue(float value, std::string message);
    void displayDebug();
};















#endif