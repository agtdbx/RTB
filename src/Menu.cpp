//
// Created by auguste on 29/01/2022.
//

#include "../include/Menu.h"
#include "../include/Functions.h"

//Private methods
void Menu::input() {
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_QUIT:
                this->run = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    this->run = false;
                }
        }
    }
}


void Menu::tick() {

}


void Menu::render() {
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderClear(this->renderer);

    SDL_Color color = {0, 0, 0, 255};
    drawText(this->renderer, "Road To Back !", 80, this->winW/2, 50, 1, color);

    SDL_RenderPresent(this->renderer);
}


//Public methods

Menu::Menu(SDL_Window *window, SDL_Renderer *renderer) {
    this->winW = 1920;
    this->winH = 1080;
    this->window = window;
    this->renderer = renderer;
    this->run = true;
}


Menu::~Menu() {
    free(this->renderer);
    free(this->window);
}


int Menu::start() {
    while(this->run){
        this->input();
        this->tick();
        this->render();
    }
    return 1;
}