#include <iostream>
#include <SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <vector>
#include <thread>
#include <chrono>

#include "../include/Game.h"
#include "../include/player.h"
#include "../include/InputHandler.h"
#include "../include/Entity.h"
#include "../include/Collision.h"
#include "../include/Spawner.h"
#include "../include/Particle.h"

Game::Game(int SCR_W, int SCR_H){
    // Set necessary variables first.
    this->running = true;
    this->SCR_W = SCR_W;
    this->SCR_H = SCR_H;
    this->window = nullptr;
    this->renderer = nullptr;

    // Gameplay variables.
    this->td = 0;
    this->tdA = new std::atomic<float>(0);
    this->xMouse = 0;
    this->yMouse = 0;
    this->xMouseG = 0;
    this->yMouseG = 0;
    this->framerate = 16.6667; // Delay between frames in ms. 16=60fps.

    // Init
    this->initEngine();
    this->initClasses();
};

// Main Game Loop.
void Game::update(){
    std::thread printTimeDeltaThread(&Game::displayDebug, this);
    while (this->running){
        // For Calculating Time Delta.
        auto start = std::chrono::high_resolution_clock::now();
        this->inputs();
        this->gameLogic();
        this->drawing();
        SDL_Delay(this->framerate - this->td);
        

        {   // For Calculating Time Delta.
            auto end = std::chrono::high_resolution_clock::now();  // End time
            auto tdelta = end - start;
            std::chrono::duration<double, std::milli> ms = tdelta;
            this->td = ms.count();  // Update Time Delta
        }
    } // Main Loop End.

    // Join the print thread before exiting
    if (printTimeDeltaThread.joinable()) {
        printTimeDeltaThread.join();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::gameLogic(){
    this->inputHandler.asses(&this->p, this->entities, &this->spawner);
    this->gameLogic_Movement();
    this->gameLogic_Collision();
}

void Game::gameLogic_Movement(){

    // Particles
    // list comprehension does not work here
    std::vector<int> collidedIndexes;
    for (int i = 0; i < entityParticles.size(); i++){
        entityParticles[i].moveExplode(&this->td);
        entityParticles[i].applyFriction(&this->td);
        entityParticles[i].applyGravity(&this->td);

        entityParticles[i].checkLifetime();

        if (entityParticles[i].getStatus() == false){
            collidedIndexes.push_back(i);
        }
    }
    spawner.removeParticles(this->entityParticles, collidedIndexes);
}

void Game::gameLogic_Collision(){
    // Play boundaries.
    Collision::collidePlayerBoundariesScreen(&this->p, this->SCR_W, this->SCR_H);
    
    {   // Movement by mouse jankyness fix.
        float centreX = (this->p.getX() + ((float)p.getW() / 2));
        float centreY = (this->p.getY() + ((float)this->p.getH() / 2));
        float threshold = 10 + this->p.getSpeed() * ((float)(this->p.getH() + (float)this->p.getH())/2);
        Collision::collideTwoPoints(centreX, centreY,this->xMouse, this->yMouse, threshold);
    }

    {   // Collision Loop
        // Allows for exact indexing of which entity was collided.
        std::vector<int> collidedIndexes;
        int i=0;

        for (auto enemy : this->entities){
            bool collided = Collision::collidePlayer_w_Entity(&this->p, &enemy);
            
            
            // Use different ifs for different collion behaviour.
            if (collided){
                collidedIndexes.push_back(i);
            }
            i++;

            {// if function needs singular index.
                for (int index : collidedIndexes){
                    spawner.explodeEnemy(&this->entities[index], this->entityParticles, 3);
                }
            }
        }

        // Make sure this is the final call.
        this->spawner.removeEnemies(this->entities, collidedIndexes);
    }// End collision loop.
}

void Game::inputs(){
    while (SDL_PollEvent(&this->event)) {
        this->closeGameWithOS(&this->event);
        this->handleMouse(&this->event);
        this->handleKeybaord(&this->event);
    }
}

void Game::drawing(){
    // Clear screen, also refreshes the draw colour to black.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);


    // Draw All Enemies
    for (auto enemy : this->entities){
        enemy.draw(this->renderer);
    };

    // Draw Player
    this->p.draw(this->renderer);

    // Draw All Particles
    for (auto particle : this->entityParticles){
        particle.draw(this->renderer);
    };

    // Render Drawn Image.
    SDL_RenderPresent(renderer);
}

// inputs helpers
void Game::closeGameWithOS(SDL_Event* event){
    if (event->type == SDL_QUIT) {
        this->running = false;
    } 
}

void Game::handleMouse(SDL_Event* event){
    if(event->type == SDL_MOUSEMOTION){
        // Gets the mouse position based on the entire screen not just the sdl window.
        SDL_GetGlobalMouseState(&this->xMouseG,&this->yMouseG);
        // Gets the mouse position based on just the sdl window.
        SDL_GetMouseState(&this->xMouse,&this->yMouse);
    }
}

void Game::handleKeybaord(SDL_Event* event){
    this->handleKeybaord_KeyDown(&this->event);
    this->handleKeybaord_KeyUp(&this->event);
}

void Game::handleKeybaord_KeyUp(SDL_Event* event){
    if (event->type == SDL_KEYUP){
        if (event->key.keysym.sym == SDLK_w) {
            this->inputHandler.w_key = false;
        }
        if (event->key.keysym.sym == SDLK_a) {
            this->inputHandler.a_key = false;
        }
        if (event->key.keysym.sym == SDLK_s) {
            this->inputHandler.s_key = false;
        }
        if (event->key.keysym.sym == SDLK_d) {
            this->inputHandler.d_key = false;
        }
        if (event->key.keysym.sym == SDLK_e) {
            this->inputHandler.e_key = false;
        }
        if (event->key.keysym.sym == SDLK_SPACE) {
            this->inputHandler.space_key = false;
        }
    }
}

void Game::handleKeybaord_KeyDown(SDL_Event* event){
    if (event->type == SDL_KEYDOWN){
        if (event->key.keysym.sym == SDLK_w) {
            this->inputHandler.w_key = true;
        }
        if (event->key.keysym.sym == SDLK_a) {
            this->inputHandler.a_key = true;
        }
        if (event->key.keysym.sym == SDLK_s) {
            this->inputHandler.s_key = true;
        }
        if (event->key.keysym.sym == SDLK_d) {
            this->inputHandler.d_key = true;
        }
        if (event->key.keysym.sym == SDLK_f) {
            spawner.spawnEnemies(this->entities, 1);
        }

        if (event->key.keysym.sym == SDLK_F3) {
            this->inputHandler.displayAllCurrentStates();
        }
        if (event->key.keysym.sym == SDLK_ESCAPE) {
            this->running = false;
        }
        if (event->key.keysym.sym == SDLK_8) {
            this->framerate = 16.6667;
        }
        if (event->key.keysym.sym == SDLK_9) {
            this->framerate = 8.3334;
        }
        if (event->key.keysym.sym == SDLK_0) {
            this->framerate = 0;
        }
        if (event->key.keysym.sym == SDLK_e) {
            this->inputHandler.e_key = true;
        }
        if (event->key.keysym.sym == SDLK_SPACE) {
            this->inputHandler.space_key = true;
        }
    }
}

void Game::initEngine(){
    SDL_Init(SDL_INIT_VIDEO);
    if (SDL_CreateWindowAndRenderer(this->SCR_W, this->SCR_H, 0, &window, &renderer) != 0) {
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        this->running = false;
        return;
    }

    int logicalWidth = 1920; // Define your logical width
    int logicalHeight = 1080; // Define your logical height

    this->windowLogicalSizeModifierDifferenceWidth = (float)logicalWidth/SCR_W;
    this->windowLogicalSizeModifierDifferenceHeight = (float)logicalHeight/SCR_H;
    SDL_RenderSetLogicalSize(renderer, logicalWidth, logicalHeight);
    // event handler variable
    SDL_Event event;
}

void Game::initClasses(){
    // Necessary Instance Object Variables and lists.
    
    // below is wrong. make sure to call the correct one.
    // https://chatgpt.com/share/6766c2d2-fcc8-800b-8fa0-10f80f099a61
    // Player p(this->SCR_W/2, this->SCR_H/2, 20, 20, 0.1, &this->td, &this->xMouseG, &this->yMouseG, &this->xMouse, &this->yMouse);
    this->p = Player(this->SCR_W/2, this->SCR_H/2, 20, 20, 1, &this->td, &this->xMouseG, &this->yMouseG, &this->xMouse, &this->yMouse, this->windowLogicalSizeModifierDifferenceWidth, this->windowLogicalSizeModifierDifferenceHeight);
    this->spawner = Spawner(&this->td, &this->SCR_W, &this->SCR_H);
    InputHandler inputHandler;
    std::vector<Entity> entities;
    std::vector<Particle> entityParticles;

    
    
}



// Getters
int Game::getScreenWidth(){
    return this->SCR_W;
}

int Game::getScreenHeight(){
    return this->SCR_H;
}

void Game::printValue(float value, std::string message) {
    std::cout << message << value << std::endl;
}

void Game::displayDebug() {
    while (this->running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Sleep for 1 second

        // Directly read the atomic `td` value
        // TWO ARROWS!
        float currentTDelta = this->td + this->framerate;  // Load the atomic value
        this->printValue(1000/currentTDelta, "FPS: ");  // Print the time delta
        this->printValue(this->entities.size(), "Enemies #: ");
        this->printValue(this->entityParticles.size(), "Entity Particles #: ");
    }
}



