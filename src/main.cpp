#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "../include/Menu.h"

int main() {
    std::cout << "Lancement ..." << std::endl;
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(SDL_INIT_EVERYTHING);
    Mix_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("RTB",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080,
                                          SDL_WINDOW_BORDERLESS);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    Menu menu = Menu(window, renderer);

    menu.start();



    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    std::cout << "Fini !" << std::endl;
    return 0;
}
