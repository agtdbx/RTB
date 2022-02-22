//
// Created by auguste on 31/01/2022.
//

#ifndef RTB_GAME_H
#define RTB_GAME_H

#include <SDL.h>
#include "../include/Button.h"
#include "../include/Personnage.h"

class Game {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int winW, winH, fenetre;
    bool run;
    Button butContinuer, butQuitter;
    Personnage perso;

    void initButton();
    void input();
    void tick();
    void render();

public:
    Game(SDL_Window *window, SDL_Renderer *renderer, int winW, int winH);
    ~Game();

    void start();
    void initLevel(int levelNum);
};


#endif //RTB_GAME_H
