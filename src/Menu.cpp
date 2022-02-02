//
// Created by auguste on 29/01/2022.
//

#include "../include/Menu.h"
#include "../include/Functions.h"

//Private methods

void Menu::initButton() {
    SDL_Color colorOff = {255, 255, 255, 0};
    SDL_Color colorOn = {200, 200, 200, 100};
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color blue = {0, 0, 255, 100};
    //Menu principal
    this->butJouer = Button("Jouer", 40, 1, this->winW/2 - 100, this->winH/2 - 100, 200, 50, colorOff, colorOn, 2, black);
    this->butOptions = Button("Options", 40, 1,this->winW/2 - 100, this->winH/2, 200, 50, colorOff, colorOn,2, black);
    this->butQuitter = Button("Quitter", 40, 1, this->winW/2 - 100, this->winH/2 + 100, 200, 50, colorOff, colorOn,2, black);

    //Choix des niveaux
    this->butlvl1 = Button("1", 40, 1,this->winW/2 - 25 - 75, this->winH/3, 50, 50, colorOff, colorOn,2, black);
    this->butlvl2 = Button("2", 40, 1,this->winW/2 - 25, this->winH/3, 50, 50, colorOff, colorOn,2, black);
    this->butlvl3 = Button("3", 40, 1,this->winW/2 - 25 + 75, this->winH/3, 50, 50, colorOff, colorOn,2, black);
    this->butRetourJouer = Button("Retour", 40, 1, this->winW/2 - 100, this->winH-50 - 100, 200, 50, colorOff, colorOn,2, black);

    //Options
    //Graphic
    this->butGraphics = Button("Graphique", 30, 2, this->spacingWithScreen + this->borderSize, 75 + this->spacingWithScreen, 250-this->borderSize*2, 75-this->borderSize*2, colorOff, colorOn,0, black);
    std::vector<char*> choixRes = {"1280x720", "1280x800", "1920x1080", "2560x1440"};
    this->butChoixRes = Select("1920x1080", 30, 1, this->winW/2 + 80, 250, 160, 40, colorOff, colorOn, choixRes, 2, black);
    this->fullScreen = Switch(this->winW/2 + 40, 360, 80, 20, colorOff, blue, 2, black);

    //Sonore
    this->butSonore = Button("Sonore", 30, 2, this->spacingWithScreen + this->borderSize, 75*2 + this->spacingWithScreen - this->borderSize, 250-this->borderSize*2, 75-this->borderSize*2, colorOff, colorOn,0, black);

    //Clavier
    this->butKeyBinding = Button("Clavier", 30, 2, this->spacingWithScreen + this->borderSize, 75*3 + this->spacingWithScreen - this->borderSize*2, 250-this->borderSize*2, 75-this->borderSize*2, colorOff, colorOn,0, black);

    //Credit
    this->butCredit = Button("Credit", 30,2, this->spacingWithScreen + this->borderSize, 75*4 + this->spacingWithScreen - this->borderSize*3, 250-this->borderSize*2, 75-this->borderSize*2, colorOff, colorOn,0, black);

    this->butRetourOptions = Button("Retour", 40, 1, this->winW/2 - 100, this->winH-50 - 100, 200, 50, colorOff, colorOn,2, black);
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
            if (this->butSonore.clicOnButton()){
                fenetre = 21;
            }
            else if (this->butKeyBinding.clicOnButton()){
                fenetre = 22;
            }
            else if(this->butCredit.clicOnButton()){
                fenetre = 23;
            }
            else if (this->butRetourOptions.clicOnButton()){
                this->fenetre = 0;
            }
            break;

        case 21:
            if (this->butGraphics.clicOnButton()){
                fenetre = 20;
            }
            else if (this->butKeyBinding.clicOnButton()){
                fenetre = 22;
            }
            else if(this->butCredit.clicOnButton()){
                fenetre = 23;
            }
            else if (this->butRetourOptions.clicOnButton()){
                this->fenetre = 0;
            }
            break;

        case 22:
            if (this->butGraphics.clicOnButton()){
                fenetre = 20;
            }
            else if (this->butSonore.clicOnButton()){
                fenetre = 21;
            }
            else if(this->butCredit.clicOnButton()){
                fenetre = 23;
            }
            else if (this->butRetourOptions.clicOnButton()){
                this->fenetre = 0;
            }
            break;

        case 23:
            if (this->butGraphics.clicOnButton()){
                fenetre = 20;
            }
            else if (this->butSonore.clicOnButton()){
                fenetre = 21;
            }
            else if(this->butKeyBinding.clicOnButton()){
                fenetre = 22;
            }
            else if (this->butRetourOptions.clicOnButton()){
                this->fenetre = 0;
            }
            break;
    }
}


void Menu::render() {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
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

        case 20:{
            drawText(this->renderer, "Road To Bac !", 80, this->winW/2, 10, 1, color);
            drawText(this->renderer, "Options graphique", 50, this->winW/2, 100, 1, color);
            SDL_SetRenderDrawColor(this->renderer, 150, 150, 150, 100);
            SDL_Rect rect = {this->spacingWithScreen + this->borderSize, 75 + this->spacingWithScreen, 250-this->borderSize*2, 75-this->borderSize*2};
            SDL_RenderFillRect(this->renderer, &rect);
            this->drawBaseOptions();

            this->drawGraphicOptions();

            this->butRetourOptions.draw(this->renderer);
            break;}

        case 21:{
            drawText(this->renderer, "Road To Bac !", 80, this->winW/2, 10, 1, color);
            drawText(this->renderer, "Options sonore", 50, this->winW/2, 100, 1, color);
            SDL_SetRenderDrawColor(this->renderer, 150, 150, 150, 100);
            SDL_Rect rect = {this->spacingWithScreen + this->borderSize, 75*2 + this->spacingWithScreen - this->borderSize, 250-this->borderSize*2, 75-this->borderSize*2};
            SDL_RenderFillRect(this->renderer, &rect);
            this->drawBaseOptions();

            this->drawSoundsOptions();

            this->butRetourOptions.draw(this->renderer);
            break;}

        case 22:{
            drawText(this->renderer, "Road To Bac !", 80, this->winW/2, 10, 1, color);
            drawText(this->renderer, "Options clavier", 50, this->winW/2, 100, 1, color);
            SDL_SetRenderDrawColor(this->renderer, 150, 150, 150, 100);
            SDL_Rect rect = {this->spacingWithScreen + this->borderSize, 75*3 + this->spacingWithScreen - this->borderSize*2, 250-this->borderSize*2, 75-this->borderSize*2};
            SDL_RenderFillRect(this->renderer, &rect);
            this->drawBaseOptions();

            this->drawKeyboardOptions();

            this->butRetourOptions.draw(this->renderer);
            break;}

        case 23:{
            drawText(this->renderer, "Road To Bac !", 80, this->winW/2, 10, 1, color);
            drawText(this->renderer, "Credit", 50, this->winW/2, 100, 1, color);
            SDL_SetRenderDrawColor(this->renderer, 150, 150, 150, 100);
            SDL_Rect rect = {this->spacingWithScreen + this->borderSize, 75*4 + this->spacingWithScreen - this->borderSize*3, 250-this->borderSize*2, 75-this->borderSize*2};
            SDL_RenderFillRect(this->renderer, &rect);
            this->drawBaseOptions();

            this->drawCredit();

            this->butRetourOptions.draw(this->renderer);
            break;}
    }

    SDL_RenderPresent(this->renderer);
}

void Menu::drawBaseOptions() {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    int x = 0;
    int y = 0;
    int width = 250;
    int height = 75;
    //Case en haut à gauche
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {x+this->spacingWithScreen+i, y+this->spacingWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }

    SDL_Color color = {0, 0, 0, 255};
    drawText(this->renderer, "Options", 40, x+width/2+this->spacingWithScreen+this->borderSize, y+ height/6 +this->spacingWithScreen+this->borderSize, 1, color);

    //Case exterieure
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {0+this->spacingWithScreen+i, 0+this->spacingWithScreen+i, 250-i*2, winH-this->spacingWithScreen*2-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }

    //Case graphique
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    y = height - this->borderSize;
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {x+this->spacingWithScreen+i, y+this->spacingWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }
    this->butGraphics.draw(this->renderer);

    //Case sonore
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    y = height*2 - this->borderSize*2;
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {x+this->spacingWithScreen+i, y+this->spacingWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }
    this->butSonore.draw(this->renderer);

    //Case keyBinding
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    y = height*3 - this->borderSize*3;
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {x+this->spacingWithScreen+i, y+this->spacingWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }
    this->butKeyBinding.draw(this->renderer);

    //Case credit
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    y = height*4 - this->borderSize*4;
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {x+this->spacingWithScreen+i, y+this->spacingWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }
    this->butCredit.draw(this->renderer);
}


void Menu::drawGraphicOptions() {
    SDL_Color color = {0, 0, 0, 255};

    //Choix résolution
    drawText(this->renderer, "Resolution de l'ecran :", 30, this->winW/2 - 80, 250, 1, color);
    this->butChoixRes.draw(this->renderer);

    //Pleins écran
    drawText(this->renderer, "Plein ecran :", 30, this->winW/2 - 80, 350, 1, color);
    this->fullScreen.draw(this->renderer);
}


void Menu::drawSoundsOptions() {

}


void Menu::drawKeyboardOptions() {

}


void Menu::drawCredit() {

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
    this->spacingWithScreen = 10;
    this->borderSize = 3;

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