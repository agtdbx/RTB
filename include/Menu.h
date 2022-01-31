//
// Created by auguste on 29/01/2022.
//

#ifndef RTB_MENU_H
#define RTB_MENU_H

#include <SDL.h>
#include "../include/Button.h"

class Menu {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int winW, winH, fenetre;
    bool run;
    Button butJouer, butOptions, butQuitter,
    butlvl1, butlvl2, butlvl3, butlvl4, butRetour;

    void initButton();
    void input();
    void tick();
    void render();

public:
    Menu(SDL_Window *window, SDL_Renderer *renderer);
    ~Menu();

    int start();
};


#endif //RTB_MENU_H
