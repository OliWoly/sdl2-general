#include <SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>

#include <iostream>
#include "../include/player.h"
#include "../include/InputHandler.h"
#include "../include/Entity.h"
#include "../include/Collision.h"
#include <list>

using namespace std;

// Constants..
int SCREENWIDTH = 1280;
int SCREENHEIGHT = 720;

int main() {
    // SDL Initialisation.
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window and renderer
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    // Further SDL Initialisation.
    if (SDL_CreateWindowAndRenderer(SCREENWIDTH, SCREENHEIGHT, 0, &window, &renderer) != 0) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }



    bool quit = false;
    SDL_Event event;

    int xMouse, yMouse;
    int xMouseG, yMouseG;

    int framerate = 16;

    

    bool wKeyPressed = false;

    // Time delta.
    float td;

    // Class Inits.
    // At bottom right before main loop.
    // This way makes sure all the vairbales have 
    // already been declared.
    list<int> pcolour{255,255,255,255};
    Player p(SCREENWIDTH/2, SCREENHEIGHT/2, 20, 20, 1, &td, &xMouseG, &yMouseG, &xMouse, &yMouse);
    Entity e1(60, 40, 100, 20, &td);
    InputHandler inputHandler;
    Collision collider;


    // Main loop
    while (!quit) {
        // Frame Timings. Initial Frame time.
        auto start = std::chrono::high_resolution_clock::now();


        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } 

            // Mouse Inputs.
            if(event.type == SDL_MOUSEMOTION)
            {
                // Gets the mouse position based on the entire screen not just the sdl window.
                SDL_GetGlobalMouseState(&xMouseG,&yMouseG);
                // Gets the mouse position based on just the sdl window.
                SDL_GetMouseState(&xMouse,&yMouse);
                //cout << xMouse << " " << yMouse << endl;
            }


            // Handle KeyDowns:
            if (event.type == SDL_KEYDOWN){
                    if (event.key.keysym.sym == SDLK_w) {
                        inputHandler.w_key = true;
                    }
                    if (event.key.keysym.sym == SDLK_a) {
                        inputHandler.a_key = true;
                    }
                    if (event.key.keysym.sym == SDLK_s) {
                        inputHandler.s_key = true;
                    }
                    if (event.key.keysym.sym == SDLK_d) {
                        inputHandler.d_key = true;
                    }

                    if (event.key.keysym.sym == SDLK_F3) {
                        inputHandler.displayAllCurrentStates();
                    }

                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        quit = true;
                    }

                    if (event.key.keysym.sym == SDLK_8) {
                        framerate = 16;
                    }

                    if (event.key.keysym.sym == SDLK_9) {
                        framerate = 8;
                    }

                    if (event.key.keysym.sym == SDLK_0) {
                        framerate = 0;
                    }

                    if (event.key.keysym.sym == SDLK_e) {
                        p.setColour(180, 20, 190, 255);
                    }


            }

            // Handle KeyUps:
            if (event.type == SDL_KEYUP){
                    if (event.key.keysym.sym == SDLK_w) {
                        inputHandler.w_key = false;
                    }
                    if (event.key.keysym.sym == SDLK_a) {
                        inputHandler.a_key = false;
                    }
                    if (event.key.keysym.sym == SDLK_s) {
                        inputHandler.s_key = false;
                    }
                    if (event.key.keysym.sym == SDLK_d) {
                        inputHandler.d_key = false;
                    }
            }
        } // end of event loop.
            

            
        // Events based on saved inputs:
        inputHandler.asses(&p);
        


        collider.collidePlayer_w_Entity(&p, &e1);
        collider.collidePlayerBoundariesScreen(&p, SCREENWIDTH, SCREENHEIGHT);
        
        
        // Clear screen, also refreshes the draw colour to black.
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // DRAWING
        ///////////////////////////////////////////////////////////////////////
        p.draw(renderer);
        e1.draw(renderer);













        ///////////////////////////////////////////////////////////////////////
        // Push to screen
        SDL_RenderPresent(renderer);

        SDL_Delay(framerate);

        // Frame Timings. End Frame Time.
        auto end = std::chrono::high_resolution_clock::now();  // End time
        auto tdelta = end - start;
        // weird ass way of doing this.
        std::chrono::duration<double, std::milli> ms = tdelta;
        float fps = 1000/ms.count();
        

        // set time delta to player through pointers.
        td = ms.count();
        //cout << fps << endl;

    }// end of main loop

    // On program quit.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}