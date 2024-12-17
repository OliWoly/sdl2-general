#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <SDL.h>

using namespace std;

// Constants..
int SCREENWIDTH = 1280;
int SCREENHEIGHT = 720;
int RECT_SPEED = 20; // Speed of rectangle movement

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

    // Rectangle position and size
    int rectX = SCREENWIDTH / 4;
    int rectY = SCREENHEIGHT / 4;
    int rectW = 200; // Width
    int rectH = 150; // Height

    bool quit = false;
    SDL_Event event;

    // Main loop
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } 
            // Handle key press events
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        rectY -= RECT_SPEED; // Move up
                        break;
                    case SDLK_DOWN:
                        rectY += RECT_SPEED; // Move down
                        break;
                    case SDLK_LEFT:
                        rectX -= RECT_SPEED; // Move left
                        break;
                    case SDLK_RIGHT:
                        rectX += RECT_SPEED; // Move right
                        break;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the rectangle at the updated position
        SDL_Rect rect = {rectX, rectY, rectW, rectH};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        // Push to screen
        SDL_RenderPresent(renderer);

        // Optional: Delay for frame rate (e.g., ~60 FPS)
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
