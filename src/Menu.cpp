//
// Created by auguste on 29/01/2022.
//

#include "../include/Menu.h"
#include "../include/Functions.h"
#include <iostream>
#include <string>
#include <sstream>

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
    this->butChoixRes = Select("1920x1080", 30, 1, this->winW/2 + 110, 250, 160, 40, colorOff, colorOn, choixRes, 2, black);
    this->fullScreen = Switch(this->winW/2 - 20, 340, 80, 20, colorOff, blue, 2, black);

    //Sonore
    this->butSonore = Button("Sonore", 30, 2, this->spacingWithScreen + this->borderSize, 75*2 + this->spacingWithScreen - this->borderSize, 250-this->borderSize*2, 75-this->borderSize*2, colorOff, colorOn,0, black);
    this->butMusiqueMoins = Button("-", 30, 1, this->winW/2 - 55, 235, 25, 35, colorOff, colorOn, 0, black);
    this->butMusiquePlus = Button("+", 30, 1, this->winW/2 + 35, 235, 25, 35, colorOff, colorOn, 0, black);
    this->butSonMoins = Button("-", 30, 1, this->winW/2 - 55, 335, 25, 35, colorOff, colorOn, 0, black);
    this->butSonPlus = Button("+", 30, 1, this->winW/2 + 35, 335, 25, 35, colorOff, colorOn, 0, black);

    //Clavier
    this->butKeyBinding = Button("Clavier", 30, 2, this->spacingWithScreen + this->borderSize, 75*3 + this->spacingWithScreen - this->borderSize*2, 250-this->borderSize*2, 75-this->borderSize*2, colorOff, colorOn,0, black);
    this->butBindGauche = Button("Changer", 30, 1, this->winW - 140 - 200, 200, 140, 40, colorOff, colorOn, 2, black);
    this->butBindDroite= Button("Changer", 30, 1, this->winW - 140 - 200, 260, 140, 40, colorOff, colorOn, 2, black);
    this->butBindSaut = Button("Changer", 30, 1, this->winW - 140 - 200, 320, 140, 40, colorOff, colorOn, 2, black);

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
                this->fenetre = 0;
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
            else if (this->butMusiqueMoins.clicOnButton() && this->volumeMusique >= 5 && (float)SDL_GetTicks()/1000 - this->lastClic > 0.3){
                this->volumeMusique -= 5;
                this->lastClic = (float)SDL_GetTicks()/1000;
            }
            else if (this->butMusiquePlus.clicOnButton() && this->volumeMusique <= 95 && (float)SDL_GetTicks()/1000 - this->lastClic > 0.3){
                this->volumeMusique += 5;
                this->lastClic = (float)SDL_GetTicks()/1000;
            }
            else if (this->butSonMoins.clicOnButton() && this->volumeSon >= 5 && (float)SDL_GetTicks()/1000 - this->lastClic > 0.3){
                this->volumeSon -= 5;
                this->lastClic = (float)SDL_GetTicks()/1000;
            }
            else if (this->butSonPlus.clicOnButton() && this->volumeSon <= 95 && (float)SDL_GetTicks()/1000 - this->lastClic > 0.3){
                this->volumeSon += 5;
                this->lastClic = (float)SDL_GetTicks()/1000;
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
            else if (this->butBindGauche.clicOnButton()){
                this->fenetre = 221;
                this->toucheABind = 'G';
            }
            else if (this->butBindDroite.clicOnButton()){
                this->fenetre = 221;
                this->toucheABind = 'D';
            }
            else if (this->butBindSaut.clicOnButton()){
                this->fenetre = 221;
                this->toucheABind = 'S';
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

        case 221:
            int keylen;
            const unsigned char *keyboard = SDL_GetKeyboardState(&keylen);

            int key = 0;

            for (int i = 0; i < keylen; ++i){
                if (keyboard[i] == 1){
                    key = i;
                    break;
                }
            }

            if (key > 0){
                if (this->toucheABind == 'G'){
                    this->toucheGauche = key;
                }
                else if (this->toucheABind == 'D'){
                    this->toucheDroite = key;
                }
                else if (this->toucheABind == 'S'){
                    this->toucheSaut = key;
                }
                this->toucheABind = 'X';
                this->fenetre = 22;
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

        case 221:
            drawText(this->renderer, "Road To Bac !", 80, this->winW/2, 10, 1, color);
            drawText(this->renderer, "Appuis sur un touche", 50, this->winW/2, this->winH/2, 1, color);
            break;
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
    drawText(this->renderer, "Resolution de l'ecran :", 30, this->winW/2 - 200, 250, 0, color);
    bool changeChoix = this->butChoixRes.draw(this->renderer);

    if (changeChoix){
        this->setScreenSize();
    }

    //Pleins écran
    drawText(this->renderer, "Plein ecran :", 30, this->winW/2 - 200, 330, 0, color);
    bool fullScreen = this->fullScreen.draw(this->renderer);

    if (fullScreen){
        this->setScreenMode();
    }
}


void Menu::drawSoundsOptions() {
    SDL_Color color = {0, 0, 0, 255};

    //Réglage de la musique
    drawText(this->renderer, "Musique", 30, this->winW/2, 200, 1, color);
    char text[10] = "000000000";
    snprintf(text, sizeof(text), "%i", this->volumeMusique);
    drawText(this->renderer, text, 25, this->winW/2 - 5, 240, 1, color);
    drawText(this->renderer, "%", 25, this->winW/2 + 25, 240, 1, color);

    this->butMusiqueMoins.draw(this->renderer);
    this->butMusiquePlus.draw(this->renderer);

    //Réglage du son
    drawText(this->renderer, "Son", 30, this->winW/2, 300, 1, color);
    char text2[10] = "000000000";
    snprintf(text2, sizeof(text2), "%i", this->volumeSon);
    drawText(this->renderer, text2, 25, this->winW/2 - 5, 340, 1, color);
    drawText(this->renderer, "%", 25, this->winW/2 + 25, 340, 1, color);

    this->butSonMoins.draw(this->renderer);
    this->butSonPlus.draw(this->renderer);
}


void Menu::drawKeyboardOptions() {
    SDL_Color color = {0, 0, 0, 255};
    //Bind déplacement à gauche
    drawText(this->renderer, "Deplacement a gauche :", 30, this->winW/2, 200, 3, color);
    drawText(this->renderer, this->drawKeyBind(this->toucheGauche), 30, this->winW/2 + 5, 200, 0, color);
    this->butBindGauche.draw(this->renderer);

    //Bind déplacement à droite
    drawText(this->renderer, "Deplacement a droite :", 30, this->winW/2, 260, 3, color);
    drawText(this->renderer, this->drawKeyBind(this->toucheDroite), 30, this->winW/2 + 5, 260, 0, color);
    this->butBindDroite.draw(this->renderer);

    //Bind saut
    drawText(this->renderer, "Saut :", 30, this->winW/2, 320, 3, color);
    drawText(this->renderer, this->drawKeyBind(this->toucheSaut), 30, this->winW/2 + 5, 320, 0, color);
    this->butBindSaut.draw(this->renderer);
}


void Menu::drawCredit() {

}


void Menu::setScreenSize() {
    char *res = this->butChoixRes.getValue();
    std::string width, height;
    bool first = false;

    for (int i = 0; i < strlen(res); ++i){
        if (res[i] == 'x'){
            first = true;
        }
        else if (!first){
            width.push_back(res[i]);
        }
        else{
            height.push_back(res[i]);
        }
    }
    std::stringstream intWidth(width);
    std::stringstream intHeight(height);

    intWidth >> this->winW;
    intHeight >> this->winH;

    SDL_SetWindowSize(this->window, this->winW, this->winH);

    this->butChoixRes.setX(this->winW/2 + 110);
    this->fullScreen.setX(this->winW/2 - 20);

    //Menu principal
    this->butJouer.setX(this->winW/2 - 100);
    this->butJouer.setY(this->winH/2 - 100);
    this->butOptions.setX(this->winW/2 - 100);
    this->butOptions.setY(this->winH/2);
    this->butQuitter.setX(this->winW/2 - 100);
    this->butQuitter.setY(this->winH/2 + 100);

    //Choix des niveaux
    this->butlvl1.setX(this->winW/2 - 25 - 75);
    this->butlvl1.setY(this->winH/3);
    this->butlvl2.setX(this->winW/2 - 25);
    this->butlvl2.setY(this->winH/3);
    this->butlvl3.setX(this->winW/2 - 25 + 75);
    this->butlvl3.setY(this->winH/3);
    this->butRetourJouer.setX(this->winW/2 - 100);
    this->butRetourJouer.setY(this->winH-50 - 100);

    //Options
    //Graphic
    this->butChoixRes.setX(this->winW/2 + 110);
    this->fullScreen.setX(this->winW/2 - 20);

    //Sonore
    this->butMusiqueMoins.setX(this->winW/2 - 55);
    this->butMusiquePlus.setX(this->winW/2 + 35);
    this->butSonMoins.setX(this->winW/2 - 55);
    this->butSonPlus.setX(this->winW/2 + 35);

    //Clavier
    this->butBindGauche.setX(this->winW - 140 - 200);
    this->butBindDroite.setX(this->winW - 140 - 200);
    this->butBindSaut.setX(this->winW - 140 - 200);

    this->butRetourOptions.setX(this->winW/2 - 100);
    this->butRetourOptions.setY(this->winH-50 - 100);
}


void Menu::setScreenMode() {
    if (this->fullScreen.isActive()){
        SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
    else{
        SDL_SetWindowFullscreen(this->window, SDL_WINDOW_SHOWN);
    }
}


char * Menu::drawKeyBind(int key){
    if (key == 44){
        return "Espace";
    }
    if (key == 79){
        return "Fleche droite";
    }
    if (key == 80){
        return "Fleche gauche";
    }
    if (key == 81){
        return "Fleche basse";
    }
    if (key == 82){
        return "Fleche haute";
    }
    if (key == 224){
        return "Control gauche";
    }
    if (key == 228){
        return "Control droit";
    }
    if (key == 225){
        return "Maj gauche";
    }
    if (key == 226){
        return "Alt gauche";
    }
    if (key == 229){
        return "Maj droit";
    }
    if (key == 230){
        return "Alt droit";
    }
    if (4 <= key && key <= 31){
        static char res = 'c';
        res = key + 93;
        return &res;
    }
    return "Non Definit";
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
    this->lastClic = 0.0;
    this->lastTime = 0.0;
    this->volumeMusique = 100;
    this->volumeSon = 100;
    this->toucheABind = 'X';
    this->toucheGauche = 20;
    this->toucheDroite = 7;
    this->toucheSaut = 44;

    this->initButton();
}


Menu::~Menu() {

}


bool Menu::start() {
    this->run = true;
    this->continuer = false;
    while(this->run){
        if (((float)SDL_GetTicks()/1000) - this->lastTime > 1.0/30){
            this->lastTime = (float)SDL_GetTicks()/1000;
            this->input();
            this->tick();
            this->render();
        }
    }
    return this->continuer;
}