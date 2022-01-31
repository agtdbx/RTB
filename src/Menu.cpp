//
// Created by auguste on 29/01/2022.
//

#include "../include/Menu.h"
#include "../include/Functions.h"
#include "../include/Button.h"

//Private methods

void Menu::initButton() {
    SDL_Color colorOff = {150, 150, 150, 255};
    SDL_Color colorOn = {200, 200, 200, 255};
    this->butJouer = Button("Jouer", 40, this->winW/2 - 100, this->winH/2 - 100, 200, 50, colorOff, colorOn);
    this->butOptions = Button("Options", 40,this->winW/2 - 100, this->winH/2, 200, 50, colorOff, colorOn);
    this->butQuitter = Button("Quitter", 40,this->winW/2 - 100, this->winH/2 + 100, 200, 50, colorOff, colorOn);
}


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
                break;
        }
    }
}


void Menu::tick() {

}


void Menu::render() {
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderClear(this->renderer);

    SDL_Color color = {0, 0, 0, 255};
    switch (this->fenetre) {
        case 0:
            this->butJouer.draw(renderer);
            this->butOptions.draw(renderer);
            this->butQuitter.draw(renderer);
            break;

        case 1:
            break;
    }
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
    this->fenetre = 0;

    this->initButton();
}


Menu::~Menu() {
}


int Menu::start() {
    while(this->run){
        this->input();
        this->tick();
        this->render();
    }
    return 1;
}