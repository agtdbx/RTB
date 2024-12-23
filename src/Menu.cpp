//
// Created by auguste on 29/01/2022.
//

#include "../include/Menu.h"
#include "../include/Functions.h"
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include <json/json.h>
#include <json/value.h>
#include <json/writer.h>
#include <json/reader.h>

//Private methods

void Menu::initButton() {
    SDL_Color colorOff = {255, 255, 255, 0};
    SDL_Color colorOn = {100, 100, 100, 100};
    SDL_Color blue = {0, 0, 255, 100};

    //Menu principal
    this->butJouer = Button((char *)"Jouer", 40, 1, this->textColor, this->winW/2 - 100, this->winH/2 - 100, 200, 50, colorOff, colorOn, 2, this->color);
    this->butOptions = Button((char *)"Options", 40, 1, this->textColor,this->winW/2 - 100, this->winH/2, 200, 50, colorOff, colorOn,2, this->color);
    this->butQuitter = Button((char *)"Quitter", 40, 1, this->textColor, this->winW/2 - 100, this->winH/2 + 100, 200, 50, colorOff, colorOn,2, this->color);

    //Choix des niveaux
    this->butlvls.push_back(Button((char *)"1", 40, 1, this->textColor,this->winW/2 - 25 - 75, this->winH/3, 50, 50, colorOff, colorOn,2, this->color));
    this->butlvls.push_back(Button((char *)"2", 40, 1, this->textColor,this->winW/2 - 25, this->winH/3, 50, 50, colorOff, colorOn,2, this->color));
    this->butlvls.push_back(Button((char *)"3", 40, 1, this->textColor,this->winW/2 - 25 + 75, this->winH/3, 50, 50, colorOff, colorOn,2, this->color));
    this->butlvls.push_back(Button((char *)"4", 40, 1, this->textColor,this->winW/2 - 25 - 75, this->winH/3 + 75, 50, 50, colorOff, colorOn,2, this->color));
    this->butRetourJouer = Button((char *)"Retour", 40, 1, this->textColor, this->winW/2 - 100, this->winH-50 - 100, 200, 50, colorOff, colorOn,2, this->color);

    //Options
    //Graphic
    this->butGraphics = Button((char *)"Graphique", 30, 2, this->textColor, this->spacingWithScreen + this->borderSize, 75 + this->spacingWithScreen, 250-this->borderSize*2, 75-this->borderSize*2, colorOff, colorOn,0, this->color);
    std::vector<char*> choixRes = { (char *)"1280x720",
                                    (char *)"1280x800",
                                    (char *)"1920x1080",
                                    (char *)"2560x1440"};

    this->butChoixRes = Select((char *)"1920x1080", 30, 1, this->textColor, this->winW/2 + 110, 250, 160, 40, colorOff, colorOn, choixRes, 2, this->color);
    this->fullScreen = Switch(this->winW/2 - 20, 340, 80, 20, colorOff, blue, 2, this->color);

    //Sonore
    this->butSonore = Button((char *)"Sonore", 30, 2, this->textColor, this->spacingWithScreen + this->borderSize, 75*2 + this->spacingWithScreen - this->borderSize, 250-this->borderSize*2, 75-this->borderSize*2, colorOff, colorOn,0, this->color);
    this->butMusiqueMoins = Button((char *)"-", 30, 1, this->textColor, this->winW/2 - 55, 235, 25, 35, colorOff, colorOn, 0, this->color);
    this->butMusiquePlus = Button((char *)"+", 30, 1, this->textColor, this->winW/2 + 35, 235, 25, 35, colorOff, colorOn, 0, this->color);
    this->butSonMoins = Button((char *)"-", 30, 1, this->textColor, this->winW/2 - 55, 335, 25, 35, colorOff, colorOn, 0, this->color);
    this->butSonPlus = Button((char *)"+", 30, 1, this->textColor, this->winW/2 + 35, 335, 25, 35, colorOff, colorOn, 0, this->color);

    //Clavier
    this->butKeyBinding = Button((char *)"Clavier", 30, 2, this->textColor, this->spacingWithScreen + this->borderSize, 75*3 + this->spacingWithScreen - this->borderSize*2, 250-this->borderSize*2, 75-this->borderSize*2, colorOff, colorOn,0, this->color);
    this->butBindHaut   = Button((char *)"Changer", 30, 1, this->textColor, this->winW - 140 - 200, 200, 140, 40, colorOff, colorOn, 2, this->color);
    this->butBindBas    = Button((char *)"Changer", 30, 1, this->textColor, this->winW - 140 - 200, 260, 140, 40, colorOff, colorOn, 2, this->color);
    this->butBindGauche = Button((char *)"Changer", 30, 1, this->textColor, this->winW - 140 - 200, 320, 140, 40, colorOff, colorOn, 2, this->color);
    this->butBindDroite = Button((char *)"Changer", 30, 1, this->textColor, this->winW - 140 - 200, 380, 140, 40, colorOff, colorOn, 2, this->color);
    this->butBindSaut   = Button((char *)"Changer", 30, 1, this->textColor, this->winW - 140 - 200, 440, 140, 40, colorOff, colorOn, 2, this->color);

    //Credit
    this->butCredit = Button((char *)"Credit", 30,2, this->textColor, this->spacingWithScreen + this->borderSize, 75*4 + this->spacingWithScreen - this->borderSize*3, 250-this->borderSize*2, 75-this->borderSize*2, colorOff, colorOn,0, this->color);

    this->butRetourOptions = Button((char *)"Retour", 40, 1, this->textColor, this->winW/2 - 100, this->winH-50 - 100, 200, 50, colorOff, colorOn,2, this->color);
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
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                fenetre = 1;
                float wait = (float)SDL_GetTicks()/1000.0f;
                while ((float)SDL_GetTicks()/1000.0f - wait < 0.1);
            }
            else if (this->butOptions.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                fenetre = 20;
            }
            else if (this->butQuitter.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                this->run = false;
            }
            break;

        case 1:
            for (int i = 0; i < this->nb_levels; i++) {
                if (this->lastLevelComplete >= i && this->butlvls[i].clicOnButton()){
                    Mix_PlayChannel(-1, this->button_clic_sound, 0);
                    this->run = false;
                    this->continuer = true;
                    this->levelLoad = i + 1;
                }
            }
            if (this->butRetourJouer.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                this->fenetre = 0;
            }
            break;

        case 20:
            if (this->butSonore.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                fenetre = 21;
            }
            else if (this->butKeyBinding.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                fenetre = 22;
            }
            else if(this->butCredit.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                fenetre = 23;
            }
            else if (this->butRetourOptions.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                this->fenetre = 0;
            }
            break;

        case 21:
            if (this->butGraphics.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                fenetre = 20;
            }
            else if (this->butKeyBinding.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                fenetre = 22;
            }
            else if(this->butCredit.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                fenetre = 23;
            }
            else if (this->butRetourOptions.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                this->fenetre = 0;
            }
            else if (this->butMusiqueMoins.clicOnButton() && this->volumeMusique >= 5 && (float)SDL_GetTicks()/1000 - this->lastClic > 0.3){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                this->volumeMusique -= 5;
                this->lastClic = (float)SDL_GetTicks()/1000;
                Mix_VolumeMusic(this->volumeMusique);
            }
            else if (this->butMusiquePlus.clicOnButton() && this->volumeMusique <= 95 && (float)SDL_GetTicks()/1000 - this->lastClic > 0.3){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                this->volumeMusique += 5;
                this->lastClic = (float)SDL_GetTicks()/1000;
                Mix_VolumeMusic(this->volumeMusique);
            }
            else if (this->butSonMoins.clicOnButton() && this->volumeSon >= 5 && (float)SDL_GetTicks()/1000 - this->lastClic > 0.3){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                this->volumeSon -= 5;
                this->lastClic = (float)SDL_GetTicks()/1000;
                Mix_Volume(-1, this->volumeSon);
            }
            else if (this->butSonPlus.clicOnButton() && this->volumeSon <= 95 && (float)SDL_GetTicks()/1000 - this->lastClic > 0.3){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                this->volumeSon += 5;
                this->lastClic = (float)SDL_GetTicks()/1000;
                Mix_Volume(-1, this->volumeSon);
            }
            break;

        case 22:
            if (this->butGraphics.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                fenetre = 20;
            }
            else if (this->butSonore.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                fenetre = 21;
            }
            else if(this->butCredit.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                fenetre = 23;
            }
            else if (this->butRetourOptions.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                this->fenetre = 0;
            }
            else if (this->butBindHaut.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                this->fenetre = 221;
                this->toucheABind = 'H';
            }
            else if (this->butBindBas.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                this->fenetre = 221;
                this->toucheABind = 'B';
            }
            else if (this->butBindGauche.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                this->fenetre = 221;
                this->toucheABind = 'G';
            }
            else if (this->butBindDroite.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                this->fenetre = 221;
                this->toucheABind = 'D';
            }
            else if (this->butBindSaut.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                this->fenetre = 221;
                this->toucheABind = 'S';
            }
            break;

        case 23:
            if (this->butGraphics.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                fenetre = 20;
            }
            else if (this->butSonore.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                fenetre = 21;
            }
            else if(this->butKeyBinding.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
                fenetre = 22;
            }
            else if (this->butRetourOptions.clicOnButton()){
                Mix_PlayChannel(-1, this->button_clic_sound, 0);
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
                if (this->toucheABind == 'H'){
                    this->toucheHaut = key;
                }
                else if (this->toucheABind == 'B'){
                    this->toucheBas = key;
                }
                else if (this->toucheABind == 'G'){
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

    SDL_Rect dst = {0, 0, this->winW, this->winH};
    SDL_RenderCopy(this->renderer, this->background, NULL, &dst);

    switch (this->fenetre) {
        case 0:
            drawText(this->renderer, (char *)"Road To Back !", 80, this->winW/2, 50, 1, this->textColor);
            this->butJouer.draw(this->renderer);
            this->butOptions.draw(this->renderer);
            this->butQuitter.draw(this->renderer);
            break;

        case 1:
            drawText(this->renderer, (char *)"Road To Back !", 80, this->winW/2, 50, 1, this->textColor);
            for (int i = 0; i < this->nb_levels; i++) {
                this->butlvls[i].draw(this->renderer);
            }
            this->butRetourJouer.draw(this->renderer);
            break;

        case 20:{
            drawText(this->renderer, (char *)"Road To Back !", 80, this->winW/2, 10, 1, this->textColor);
            drawText(this->renderer, (char *)"Options graphique", 50, this->winW/2, 100, 1, this->textColor);
            SDL_SetRenderDrawColor(this->renderer, 150, 150, 150, 100);
            SDL_Rect rect = {this->spacingWithScreen + this->borderSize, 75 + this->spacingWithScreen, 250-this->borderSize*2, 75-this->borderSize*2};
            SDL_RenderFillRect(this->renderer, &rect);
            this->drawBaseOptions();

            this->drawGraphicOptions();

            this->butRetourOptions.draw(this->renderer);
            break;}

        case 21:{
            drawText(this->renderer, (char *)"Road To Back !", 80, this->winW/2, 10, 1, this->textColor);
            drawText(this->renderer, (char *)"Options sonore", 50, this->winW/2, 100, 1, this->textColor);
            SDL_SetRenderDrawColor(this->renderer, 150, 150, 150, 100);
            SDL_Rect rect = {this->spacingWithScreen + this->borderSize, 75*2 + this->spacingWithScreen - this->borderSize, 250-this->borderSize*2, 75-this->borderSize*2};
            SDL_RenderFillRect(this->renderer, &rect);
            this->drawBaseOptions();

            this->drawSoundsOptions();

            this->butRetourOptions.draw(this->renderer);
            break;}

        case 22:{
            drawText(this->renderer, (char *)"Road To Back !", 80, this->winW/2, 10, 1, this->textColor);
            drawText(this->renderer, (char *)"Options clavier", 50, this->winW/2, 100, 1, this->textColor);
            SDL_SetRenderDrawColor(this->renderer, 150, 150, 150, 100);
            SDL_Rect rect = {this->spacingWithScreen + this->borderSize, 75*3 + this->spacingWithScreen - this->borderSize*2, 250-this->borderSize*2, 75-this->borderSize*2};
            SDL_RenderFillRect(this->renderer, &rect);
            this->drawBaseOptions();

            this->drawKeyboardOptions();

            this->butRetourOptions.draw(this->renderer);
            break;}

        case 23:{
            drawText(this->renderer, (char *)"Road To Back !", 80, this->winW/2, 10, 1, this->textColor);
            drawText(this->renderer, (char *)"Credit", 50, this->winW/2, 100, 1, this->textColor);
            SDL_SetRenderDrawColor(this->renderer, 150, 150, 150, 100);
            SDL_Rect rect = {this->spacingWithScreen + this->borderSize, 75*4 + this->spacingWithScreen - this->borderSize*3, 250-this->borderSize*2, 75-this->borderSize*2};
            SDL_RenderFillRect(this->renderer, &rect);
            this->drawBaseOptions();

            this->drawCredit();

            this->butRetourOptions.draw(this->renderer);
            break;}

        case 221:
            drawText(this->renderer, (char *)"Road To Back !", 80, this->winW/2, 10, 1, this->textColor);
            drawText(this->renderer, (char *)"Appuis sur une touche", 50, this->winW/2, this->winH/2, 1, this->textColor);
            break;
    }
    SDL_RenderPresent(this->renderer);
}

void Menu::drawBaseOptions() {
    SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a);
    int x = 0;
    int y = 0;
    int width = 250;
    int height = 75;
    //Case en haut à gauche
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {x+this->spacingWithScreen+i, y+this->spacingWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }

    drawText(this->renderer, (char *)"Options", 40, x+width/2+this->spacingWithScreen+this->borderSize, y+ height/6 +this->spacingWithScreen+this->borderSize, 1, this->textColor);

    //Case exterieure
    SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a);
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {0+this->spacingWithScreen+i, 0+this->spacingWithScreen+i, 250-i*2, winH-this->spacingWithScreen*2-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }

    //Case graphique
    SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a);
    y = height - this->borderSize;
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {x+this->spacingWithScreen+i, y+this->spacingWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }
    this->butGraphics.draw(this->renderer);

    //Case sonore
    SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a);
    y = height*2 - this->borderSize*2;
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {x+this->spacingWithScreen+i, y+this->spacingWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }
    this->butSonore.draw(this->renderer);

    //Case keyBinding
    SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a);
    y = height*3 - this->borderSize*3;
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {x+this->spacingWithScreen+i, y+this->spacingWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }
    this->butKeyBinding.draw(this->renderer);

    //Case credit
    SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a);
    y = height*4 - this->borderSize*4;
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {x+this->spacingWithScreen+i, y+this->spacingWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }
    this->butCredit.draw(this->renderer);
}


void Menu::drawGraphicOptions() {
    //Choix résolution
    drawText(this->renderer, (char *)"Resolution de l'ecran :", 30, this->winW/2 - 200, 250, 0, this->textColor);
    bool changeChoix = this->butChoixRes.draw(this->renderer);

    if (changeChoix){
        this->setScreenSize();
    }

    //Pleins écran
    drawText(this->renderer, (char *)"Plein ecran :", 30, this->winW/2 - 200, 330, 0, this->textColor);
    bool fullScreen = this->fullScreen.draw(this->renderer);

    if (fullScreen){
        this->setScreenMode();
    }
}


void Menu::drawSoundsOptions() {
    //Réglage de la musique
    drawText(this->renderer, (char *)"Musique", 30, this->winW/2, 200, 1, this->textColor);
    char text[10] = "000000000";
    snprintf(text, sizeof(text), "%i", this->volumeMusique);
    drawText(this->renderer, text, 25, this->winW/2 - 5, 240, 1, this->textColor);
    drawText(this->renderer, (char *)"%", 25, this->winW/2 + 25, 240, 1, this->textColor);

    this->butMusiqueMoins.draw(this->renderer);
    this->butMusiquePlus.draw(this->renderer);

    //Réglage du son
    drawText(this->renderer, (char *)"Son", 30, this->winW/2, 300, 1, this->textColor);
    char text2[10] = "000000000";
    snprintf(text2, sizeof(text2), "%i", this->volumeSon);
    drawText(this->renderer, text2, 25, this->winW/2 - 5, 340, 1, this->textColor);
    drawText(this->renderer, (char *)"%", 25, this->winW/2 + 25, 340, 1, this->textColor);

    this->butSonMoins.draw(this->renderer);
    this->butSonPlus.draw(this->renderer);
}


void Menu::drawKeyboardOptions() {
    //Bind déplacement en haut
    drawText(this->renderer, (char *)"Deplacement en haut :", 30, this->winW/2, 200, 3, this->textColor);
    drawText(this->renderer, this->drawKeyBind(this->toucheHaut), 30, this->winW/2 + 5, 200, 0, this->textColor);
    this->butBindHaut.draw(this->renderer);

    //Bind déplacement en bas
    drawText(this->renderer, (char *)"Deplacement en bas :", 30, this->winW/2, 260, 3, this->textColor);
    drawText(this->renderer, this->drawKeyBind(this->toucheBas), 30, this->winW/2 + 5, 260, 0, this->textColor);
    this->butBindBas.draw(this->renderer);

    //Bind déplacement à gauche
    drawText(this->renderer, (char *)"Deplacement a gauche :", 30, this->winW/2, 320, 3, this->textColor);
    drawText(this->renderer, this->drawKeyBind(this->toucheGauche), 30, this->winW/2 + 5, 320, 0, this->textColor);
    this->butBindGauche.draw(this->renderer);

    //Bind déplacement à droite
    drawText(this->renderer, (char *)"Deplacement a droite :", 30, this->winW/2, 380, 3, this->textColor);
    drawText(this->renderer, this->drawKeyBind(this->toucheDroite), 30, this->winW/2 + 5, 380, 0, this->textColor);
    this->butBindDroite.draw(this->renderer);

    //Bind saut
    drawText(this->renderer, (char *)"Saut :", 30, this->winW/2, 440, 3, this->textColor);
    drawText(this->renderer, this->drawKeyBind(this->toucheSaut), 30, this->winW/2 + 5, 440, 0, this->textColor);
    this->butBindSaut.draw(this->renderer);
}


void Menu::drawCredit() {
    // Createur
    drawText(this->renderer, (char *)"Jeu creer par", 35, this->winW/2, 200, 1, this->textColor);
    drawText(this->renderer, (char *)"Auguste Deroubaix", 50, this->winW/2, 250, 1, this->textColor);

    // Musiques
    drawText(this->renderer, (char *)"Musiques", 35, this->winW/3, 320, 1, this->textColor);
    drawText(this->renderer, (char *)"Musique menu : Context Sensitive", 25, this->winW/3, 370, 1, this->textColor);
    drawText(this->renderer, (char *)"Musique jeu : Context Sensitive", 25, this->winW/3, 410, 1, this->textColor);

    // Images
    drawText(this->renderer, (char *)"Images", 35, this->winW/3 * 2, 320, 1, this->textColor);
    drawText(this->renderer, (char *)"Fond du menu : Nrin", 25, this->winW/3 * 2, 370, 1, this->textColor);

    // Version
    drawText(this->renderer, (char *)"Alpha 1.0", 35, this->winW/2, this->winH - 200, 1, this->textColor);
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
    int x = -1;
    int y = 0;

    for (int i = 0; i < nb_levels; i++){
        this->butlvls[i].setX(this->winW/2 - 25 + (x * 75));
        this->butlvls[i].setY(this->winH/3 + (y * 75));

        x++;
        if (x > 1){
            x = -1;
            y++;
        }
    }
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
        return (char *)"Espace";
    }
    if (key == 79){
        return (char *)"Fleche droite";
    }
    if (key == 80){
        return (char *)"Fleche gauche";
    }
    if (key == 81){
        return (char *)"Fleche basse";
    }
    if (key == 82){
        return (char *)"Fleche haute";
    }
    if (key == 224){
        return (char *)"Control gauche";
    }
    if (key == 228){
        return (char *)"Control droit";
    }
    if (key == 225){
        return (char *)"Maj gauche";
    }
    if (key == 226){
        return (char *)"Alt gauche";
    }
    if (key == 229){
        return (char *)"Maj droit";
    }
    if (key == 230){
        return (char *)"Alt droit";
    }
    if (4 <= key && key <= 31){
        static char res = 'c';
        res = key + 93;
        return &res;
    }
    return (char *)"Non Definit";
}


void Menu::saveOptions() {
    Json::Value json;
    // Sauvegarde des options
    std::ofstream myfile;
    myfile.open ("./data/saves/options.json"); // Ouverture du fichier

    json["resolution"] = this->butChoixRes.getValue();
    json["winW"] = this->winW;
    json["winH"] = this->winH;
    json["fullscreen"] = this->fullScreen.isActive();
    json["volumeMusique"] = this->volumeMusique;
    json["volumeSon"] = this->volumeSon;
    json["toucheHaut"] = this->toucheHaut;
    json["toucheBas"] = this->toucheBas;
    json["toucheGauche"] = this->toucheGauche;
    json["toucheDroite"] = this->toucheDroite;
    json["toucheSaut"] = this->toucheSaut;
    json["lastLevelComplete"] = this->lastLevelComplete;

    Json::StyledWriter writer;
    myfile << writer.write(json);

    myfile.close();
}


void Menu::loadOptions() {
    Json::Value json;
    Json::Reader reader;
    std::ifstream myfile ("./data/saves/options.json");// Ouverture du fichier
    reader.parse(myfile, json);

    this->butChoixRes.setValue(json["resolution"].asString());
    this->winW = json["winW"].asInt();
    this->winH = json["winH"].asInt();
    this->fullScreen.setActive(json["fullscreen"].asBool());
    this->volumeMusique = json["volumeMusique"].asInt();
    this->volumeSon = json["volumeSon"].asInt();
    this->toucheHaut= json["toucheHaut"].asInt();
    this->toucheBas= json["toucheBas"].asInt();
    this->toucheGauche = json["toucheGauche"].asInt();
    this->toucheDroite = json["toucheDroite"].asInt();
    this->toucheSaut = json["toucheSaut"].asInt();
    this->lastLevelComplete = json["lastLevelComplete"].asInt();

    myfile.close();
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
    this->toucheHaut = 7;
    this->toucheBas = 44;
    this->toucheDroite = 7;
    this->toucheSaut = 44;
    this->lastLevelComplete = 0;
    this->levelLoad = 0;
    this->color = {100, 100, 100, 255};
    this->textColor = {150, 150, 150, 255};
    this->background = getTexture(this->renderer, "menuBackground");
    this->menu_theme = Mix_LoadMUS("./data/sounds/menu_theme.wav");
    this->button_clic_sound = Mix_LoadWAV("./data/sounds/button.wav");
    this->nb_levels = 3;

    this->initButton();

    this->loadOptions();
    this->setLastLevelComplete(0);

    this->setScreenSize();
    this->setScreenMode();
}


Menu::~Menu() {
    Mix_FreeMusic(this->menu_theme);
    Mix_FreeChunk(this->button_clic_sound);
    SDL_DestroyTexture(this->background);
}


bool Menu::start() {
    this->run = true;
    this->continuer = false;
    this->levelLoad = 0;
    Mix_PlayMusic(this->menu_theme, -1);
    Mix_VolumeMusic(this->volumeMusique);
    Mix_Volume(-1, this->volumeSon);
    while(this->run){
        if (((float)SDL_GetTicks()/1000) - this->lastTime > 1.0f/30.0f){
            this->lastTime = (float)SDL_GetTicks()/1000;
            this->input();
            this->tick();
            this->render();
        }
    }
    Mix_HaltMusic();
    this->saveOptions();

    if (this->continuer){
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
        SDL_RenderClear(this->renderer);
        SDL_Rect dst = {0, 0, this->winW, this->winH};
        SDL_RenderCopy(this->renderer, this->background, NULL, &dst);
        drawText(this->renderer, (char *)"Chargement ...", 40, this->winW / 2, this->winH / 2, 1, this->color);
        SDL_RenderPresent(this->renderer);
    }

    return this->continuer;
}


int Menu::getNumLevel() {
    return this->levelLoad;
}


int Menu::getVolumeSon() {
    return this->volumeSon;
}


int Menu::getVolumeMusique() {
    return this->volumeMusique;
}


int Menu::getToucheHaut() {
    return this->toucheHaut;
}


int Menu::getToucheBas() {
    return this->toucheBas;
}


int Menu::getToucheGauche() {
    return this->toucheGauche;
}


int Menu::getToucheDroite() {
    return this->toucheDroite;
}


int Menu::getToucheSaut() {
    return this->toucheSaut;
}


int Menu::getWinWidth() {
    return this->winW;
}


int Menu::getWinHeight() {
    return this->winH;
}


void Menu::setLastLevelComplete(int level){
    if (this->lastLevelComplete <= level)
        this->lastLevelComplete = level;

    SDL_Color colorOff = {255, 255, 255, 0};
    SDL_Color colorOn = {100, 100, 100, 100};

    SDL_Color lvl_complete = {50, 255, 50, 255};
    SDL_Color lvl_lock = {255, 50, 50, 255};

    for (int i = 0; i < this->nb_levels; i++) {
        if (i < this->lastLevelComplete)
            this->butlvls[i].setColors(colorOff, colorOn, lvl_complete, lvl_complete);
        else if (i == this->lastLevelComplete)
            this->butlvls[i].setColors(colorOff, colorOn, this->textColor, this->color);
        else
            this->butlvls[i].setColors(colorOff, colorOff, lvl_lock, lvl_lock);
    }
}
