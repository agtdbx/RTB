//
// Created by auguste on 31/01/2022.
//

#include "../include/Game.h"
#include "../include/Functions.h"
#include <SDL.h>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>

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


        float delta = ((float)SDL_GetTicks()/1000.0f) - this->lastTime;

        if (keyboard[SDL_SCANCODE_F4]) {
            this->showFps = !this->showFps;
        }
        if (this->showFps && (int)SDL_GetTicks()%100 == 0){
            this->fps = 1.0f / delta;
        }


        if (keyboard[this->toucheGauche]) {
            this->perso.deplacementX(-this->perso.getAcceleration());
        }
        else if (keyboard[this->toucheDroite]) {
            this->perso.deplacementX(this->perso.getAcceleration());
        }
        else{
            this->perso.stopVx();
        }

        if (keyboard[this->toucheSaut]) {
            this->perso.saut(this->perso.getAcceleration(), this->map);
        }

        this->perso.addVy(this->gravity);
        this->perso.move(delta, this->camera, this->map);
    }
    else {
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

            this->map.draw(this->renderer, this->camera, this->winW, this->winH);

            this->perso.draw(this->renderer, this->camera);

            if (this->showFps){
                SDL_Color green = {0, 200, 0, 255};
                char strfps[10] = "000000000";
                snprintf(strfps, sizeof(strfps), "%f", this->fps);
                drawText(this->renderer, strfps, 20, this->winW, 0, 3, green);
            }

            break;

        case 1:
            this->butContinuer.draw(this->renderer);
            this->butQuitter.draw(this->renderer);
            break;
    }

    SDL_RenderPresent(this->renderer);
}


//Public methods
Game::Game(SDL_Renderer *renderer, int winW, int winH) {
    this->winW = winW;
    this->winH = winH;
    this->renderer = renderer;
    this->run = true;
    this->fenetre = 0;
    this->volumeSon = 100;
    this->volumeMusique = 100;
    this->toucheGauche = 20;
    this->toucheDroite = 7;
    this->toucheSaut = 44;
    this->lastTime = ((float)SDL_GetTicks()/1000.0f);
    this->camera = Camera();
    this->showFps = false;
    this->fps = 0.0f;
    this->gravity = 40.0f;

    this->initButton();
}


Game::~Game() {

}


void Game::start() {
    this->run = true;
    this->fenetre = 0;
    while(this->run){
        if (((float)SDL_GetTicks()/1000) - this->lastTime >= 1.0f/60.0f){
            this->input();
            this->tick();
            this->render();
        }
    }
    float wait = (float)SDL_GetTicks()/1000.0f;
    while ((float)SDL_GetTicks()/1000.0f - wait < 0.2){}
}


void Game::initLevel(int levelNum) {
    this->map = Map(160, 90, 20*20, 70*20);
    this->perso = Personnage(this->map.getStartX(), this->map.getStartY());
    this->camera.setPos(this->perso.getX() + (this->perso.getWidth()/2) - this->winW/2, this->perso.getY() - (this->winH/4)*3);
}


void Game::setVariables(int volumeSon, int volumeMusique, int toucheGauche, int toucheDroite, int toucheSaut, int winWidth, int winHeight) {
    this->volumeSon = volumeSon;
    this->volumeMusique = volumeMusique;
    this->toucheGauche = toucheGauche;
    this->toucheDroite = toucheDroite;
    this->toucheSaut = toucheSaut;
    this->winW = winWidth;
    this->winH = winHeight;

    this->butContinuer.setX(this->winW/2 - 100);
    this->butContinuer.setY(this->winH/2 - 75);
    this->butQuitter.setX(this->winW/2 - 100);
    this->butQuitter.setY(this->winH/2 + 25);
}