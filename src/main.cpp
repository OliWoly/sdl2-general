#include <SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include "../include/Game.h"

int main() {

    Game game(1280, 720);
    game.update();

    return 0;
}