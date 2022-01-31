//
// Created by auguste on 31/01/2022.
//

#ifndef RTB_GAME_H
#define RTB_GAME_H

#include <SDL.h>
#include "../include/Button.h"

class Game {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int winW, winH, fenetre;
    bool run;
    Button butContinuer, butQuitter;

    void initButton();
    void input();
    void tick();
    void render();

public:
    Game(SDL_Window *window, SDL_Renderer *renderer, int winW, int winH);
    ~Game();

    void start();
};


#endif //RTB_GAME_H
