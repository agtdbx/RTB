//
// Created by auguste on 31/01/2022.
//

#include "../include/Game.h"
#include <SDL.h>
#include "../include/Button.h"
#include <iostream>
#include "../include/Personnage.h"

//Private methods
void Game::initButton() {
    SDL_Color colorOff = {255, 255, 255, 0};
    SDL_Color colorOn = {200, 200, 200, 100};
    SDL_Color black = {0, 0, 0, 255};
    this->butContinuer = Button("Continuer", 40, 1, this->winW/2 - 100, this->winH/2 - 75, 200, 50, colorOff, colorOn,2, black);
    this->butQuitter = Button("Quitter", 40, 1, this->winW/2 - 100, this->winH/2 + 25, 200, 50, colorOff, colorOn,2, black);
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
    if (this->fenetre == 0){
        int keylen;
        const unsigned char *keyboard = SDL_GetKeyboardState(&keylen);

        if (keyboard[this->toucheGauche]) {
            this->perso.addVx(-this->perso.getAcceleration());
        }
        else if (keyboard[this->toucheDroite]) {
            this->perso.addVx(this->perso.getAcceleration());
        }
        else{
            this->perso.stopVx();
        }

        float delta = ((float)SDL_GetTicks()/1000.0f) - this->lastTime;
        this->perso.move(delta);
    }
    else if (this->fenetre == 1){
        if (this->butContinuer.clicOnButton()){
            this->fenetre = 0;
        }
        else if (this->butQuitter.clicOnButton()){
            this->run = false;
        }
    }
    this->lastTime = ((float)SDL_GetTicks()/1000.0f);
}


void Game::render() {
    switch (this->fenetre) {
        case 0:
            SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
            SDL_RenderClear(this->renderer);

            this->perso.draw(this->renderer);

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
    this->volumeSon = 100;
    this->volumeMusique = 100;
    this->toucheGauche = 20;
    this->toucheDroite = 7;
    this->toucheSaut = 44;
    this->lastTime = ((float)SDL_GetTicks()/1000.0f);

    this->initButton();
}


Game::~Game() {

}


void Game::start() {
    this->run = true;
    this->fenetre = 0;
    while(this->run){
        this->input();
        this->tick();
        this->render();
    }
    float wait = SDL_GetTicks()/1000;
    while (SDL_GetTicks()/1000 - wait < 0.2){}
}


void Game::initLevel(int levelNum) {
    this->perso = Personnage(100.0f, 100.0f);
}


void Game::setVariables(int volumeSon, int volumeMusique, int toucheGauche, int toucheDroite, int toucheSaut) {
    this->volumeSon = volumeSon;
    this->volumeMusique = volumeMusique;
    this->toucheGauche = toucheGauche;
    this->toucheDroite = toucheDroite;
    this->toucheSaut = toucheSaut;
}