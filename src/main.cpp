#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "../include/Menu.h"
#include "../include/Game.h"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    int winW = 1920;
    int winH = 1080;

    SDL_Window *window = SDL_CreateWindow("RTB",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winW, winH,
                                          SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    Menu menu = Menu(window, renderer, winW, winH);
    Game game = Game(renderer, winW, winH);

    bool run = true;
    while (run){
        if (menu.start()){
            game.setVariables(  menu.getVolumeSon() , menu.getVolumeMusique(), menu.getToucheHaut(), menu.getToucheBas() , menu.getToucheGauche(), menu.getToucheDroite(), menu.getToucheSaut(), menu.getWinWidth(), menu.getWinHeight());
            game.initLevel(menu.getNumLevel());
            int lvl = game.start();
            menu.setLastLevelComplete(lvl);
        }
        else
            run = false;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
