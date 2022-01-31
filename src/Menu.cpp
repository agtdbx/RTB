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

    //Options
    this->butRetourOptions = Button("Retour", 40, this->winW/2 - 100, this->winH-50 - 100, 200, 50, colorOff, colorOn);
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
                    if (this->fenetre != 0){
                        this->fenetre = 0;
                    }
                    else{
                        this->run = false;
                    }
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
                fenetre = 20;
            }
            else if (this->butQuitter.clicOnButton()){
                this->run = false;
            }
            break;

        case 1:
            if (this->butlvl1.clicOnButton()){
                this->run = false;
                this->continuer = true;
            }
            else if (this->butRetourJouer.clicOnButton()){
                this->fenetre = 0;
            }
            break;

        case 20:
            if (this->butRetourOptions.clicOnButton()){
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
            drawText(this->renderer, "Road To Bac !", 80, this->winW/2, 50, 1, color);
            this->butJouer.draw(this->renderer);
            this->butOptions.draw(this->renderer);
            this->butQuitter.draw(this->renderer);

            break;

        case 1:
            drawText(this->renderer, "Road To Bac !", 80, this->winW/2, 50, 1, color);
            this->butlvl1.draw(this->renderer);
            this->butlvl2.draw(this->renderer);
            this->butlvl3.draw(this->renderer);
            this->butRetourJouer.draw(this->renderer);
            break;

        case 20:
            drawText(this->renderer, "Road To Bac !", 80, this->winW/2, 10, 1, color);
            this->drawBaseOptions();
            this->butRetourOptions.draw(this->renderer);
    }

    SDL_RenderPresent(this->renderer);
}

void Menu::drawBaseOptions() {
    int spaceWithScreen = 10;
    int borderSize = 3;
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    int x = 0;
    int y = 0;
    int width = 250;
    int height = 75;
    //Case en haut à gauceh
    for (int i = 0; i < borderSize; ++i){
        SDL_Rect rect = {x+spaceWithScreen+i, y+spaceWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }

    SDL_Color color = {0, 0, 0, 255};
    drawText(this->renderer, "Options", 40, x+width/2+spaceWithScreen+borderSize, y+height/2+spaceWithScreen+borderSize, 2, color);

    // Case entière
    for (int i = 0; i < borderSize; ++i){
        SDL_Rect rect = {0+spaceWithScreen+i, 0+spaceWithScreen+i, 250-i*2, winH-spaceWithScreen*2-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }

    y = height - borderSize;
    for (int i = 0; i < borderSize; ++i){
        SDL_Rect rect = {x+spaceWithScreen+i, y+spaceWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }

    y = height*2 - borderSize*2;
    for (int i = 0; i < borderSize; ++i){
        SDL_Rect rect = {x+spaceWithScreen+i, y+spaceWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }

    y = height*3 - borderSize*3;
    for (int i = 0; i < borderSize; ++i){
        SDL_Rect rect = {x+spaceWithScreen+i, y+spaceWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }

    y = height*4 - borderSize*4;
    for (int i = 0; i < borderSize; ++i){
        SDL_Rect rect = {x+spaceWithScreen+i, y+spaceWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }
}


//Public methods
Menu::Menu(SDL_Window *window, SDL_Renderer *renderer, int winW, int winH) {
    this->winW = winW;
    this->winH = winH;
    this->window = window;
    this->renderer = renderer;
    this->run = true;
    this->fenetre = 0;
    this->continuer = false;

    this->initButton();
}


Menu::~Menu() {
}


bool Menu::start() {
    this->run = true;
    this->continuer = false;
    while(this->run){
        this->input();
        this->tick();
        this->render();
    }
    return this->continuer;
}