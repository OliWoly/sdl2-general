#include <SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <iostream>
#include "../include/player.h"

using namespace std;

// Constants..
int SCREENWIDTH = 1280;
int SCREENHEIGHT = 720;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window and renderer
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (SDL_CreateWindowAndRenderer(SCREENWIDTH, SCREENHEIGHT, 0, &window, &renderer) != 0) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    Player p(SCREENWIDTH/2, SCREENHEIGHT/2, 20, 20, 5);

    bool quit = false;
    SDL_Event event;

    int xMouse, yMouse;

    // Main loop
    while (!quit) {
        // Frame Timings. Initial Frame time.
        auto start = std::chrono::high_resolution_clock::now();


        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } 
            // Handle key press events
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        p.stepUp(p.getSpeed());
                        break;
                    case SDLK_DOWN:
                        p.stepDown(p.getSpeed());
                        break;
                    case SDLK_LEFT:
                        p.stepLeft(p.getSpeed());
                        break;
                    case SDLK_RIGHT:
                        p.stepRight(p.getSpeed());
                        break;
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                }
            }
            if(event.type == SDL_MOUSEMOTION)
            {
                // Gets the mouse position based on the entire screen not just the sdl window.
                //SDL_GetGlobalMouseState(&xMouse,&yMouse);
                
                // Gets the mouse position based on just the sdl window.
                SDL_GetMouseState(&xMouse,&yMouse);

                cout << xMouse << " " << yMouse << endl;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        p.draw(renderer);

        // Push to screen
        SDL_RenderPresent(renderer);

















        // Frame Timings. End Frame Time.
        auto end = std::chrono::high_resolution_clock::now();  // End time
        auto tdelta = end - start;
        // weird ass way of doing this.
        std::chrono::duration<double, std::milli> ms = tdelta;
        float fps = 1000/ms.count();
        //cout << fps << endl;
    }// end of main loop

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
