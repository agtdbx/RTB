#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "../include/Menu.h"
#include "../include/Game.h"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(SDL_INIT_EVERYTHING);
    Mix_Init(SDL_INIT_EVERYTHING);

    int winW = 1920;
    int winH = 1080;

    SDL_Window *window = SDL_CreateWindow("RTB",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winW, winH,
                                          SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    Menu menu = Menu(window, renderer, winW, winH);
    Game game = Game(window, renderer, winW, winH);

    bool run = true;
    bool continuer = true;
    while (run){
        continuer = menu.start();
        if (!continuer){
            run = false;
        }
        else{
            game.initLevel(menu.getNumLevel());
            game.start();
        }
    }

    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
