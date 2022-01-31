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
    //Menu principal
    this->butJouer = Button("Jouer", 40, this->winW/2 - 100, this->winH/2 - 100, 200, 50, colorOff, colorOn);
    this->butOptions = Button("Options", 40,this->winW/2 - 100, this->winH/2, 200, 50, colorOff, colorOn);
    this->butQuitter = Button("Quitter", 40,this->winW/2 - 100, this->winH/2 + 100, 200, 50, colorOff, colorOn);

    //Choix des niveaux
    this->butlvl1 = Button("1", 40,this->winW/2 - 25 - 75, this->winH/3, 50, 50, colorOff, colorOn);
    this->butlvl2 = Button("2", 40,this->winW/2 - 25, this->winH/3, 50, 50, colorOff, colorOn);
    this->butlvl3 = Button("3", 40,this->winW/2 - 25 + 75, this->winH/3, 50, 50, colorOff, colorOn);
    this->butRetourJouer = Button("Retour", 40, this->winW/2 - 100, this->winH-50 - 100, 200, 50, colorOff, colorOn);
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
    switch (this->fenetre) {
        case 0:
            if (this->butJouer.clicOnButton()){
                fenetre = 1;
            }
            else if (this->butOptions.clicOnButton()){
                fenetre = 2;
            }
            else if (this->butQuitter.clicOnButton()){
                this->run = false;
            }
            break;

        case 1:
            if (this->butRetourJouer.clicOnButton()){
                this->fenetre = 0;
            }
            break;
    }
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
            this->butlvl1.draw(renderer);
            this->butlvl2.draw(renderer);
            this->butlvl3.draw(renderer);
            this->butRetourJouer.draw(renderer);
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