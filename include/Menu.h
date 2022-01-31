//
// Created by auguste on 29/01/2022.
//

#ifndef RTB_MENU_H
#define RTB_MENU_H

#include <SDL.h>

class Menu {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int winW, winH;
    bool run;

    void input();
    void tick();
    void render();

public:
    Menu(SDL_Window *window, SDL_Renderer *renderer);
    ~Menu();

    int start();
};


#endif //RTB_MENU_H
