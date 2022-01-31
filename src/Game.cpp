//
// Created by auguste on 31/01/2022.
//

#include "../include/Game.h"
#include <SDL.h>
#include "../include/Button.h"

//Private methods
void Game::initButton() {
    SDL_Color colorOff = {150, 150, 150, 255};
    SDL_Color colorOn = {200, 200, 200, 255};
    this->butContinuer = Button("Continuer", 40, this->winW/2 - 100, this->winH/2 - 75, 200, 50, colorOff, colorOn);
    this->butQuitter = Button("Quitter", 40, this->winW/2 - 100, this->winH/2 + 25, 200, 50, colorOff, colorOn);
}

void Game::input() {
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_QUIT:
                this->run = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    if (this->fenetre == 0){
                        this->fenetre = 1;
                    }
                    else{
                        this->fenetre = 0;
                    }
                }
                break;
        }
    }
}


void Game::tick() {
    if (this->fenetre == 1){
        if (this->butContinuer.clicOnButton()){
            this->fenetre = 0;
        }
        else if (this->butQuitter.clicOnButton()){
            this->run = false;
        }
    }
}


void Game::render() {
    switch (this->fenetre) {
        case 0:
            SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
            SDL_RenderClear(this->renderer);
            break;

        case 1:
            this->butContinuer.draw(this->renderer);
            this->butQuitter.draw(this->renderer);
            break;
    }

    SDL_RenderPresent(this->renderer);
}


//Public methods
Game::Game(SDL_Window *window, SDL_Renderer *renderer, int winW, int winH) {
    this->winW = winW;
    this->winH = winH;
    this->window = window;
    this->renderer = renderer;
    this->run = true;
    this->fenetre = 0;

    this->initButton();
}


Game::~Game() {

}


void Game::start() {
    this->run = true;
    while(this->run){
        this->input();
        this->tick();
        this->render();
    }
}