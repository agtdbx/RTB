//
// Created by auguste on 29/01/2022.
//

#ifndef RTB_MENU_H
#define RTB_MENU_H

#include <SDL.h>
#include "../include/Button.h"
#include "../include/Select.h"
#include "../include/Switch.h"

class Menu {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int winW, winH, fenetre, spacingWithScreen, borderSize, volumeMusique, volumeSon, toucheGauche, toucheDroite, toucheSaut;
    float lastClic, lastTime;
    bool run, continuer;
    char toucheABind;
    Button butJouer, butOptions, butQuitter,
    butlvl1, butlvl2, butlvl3, butRetourJouer,
    butGraphics,
    butSonore, butMusiqueMoins, butMusiquePlus, butSonMoins, butSonPlus,
    butKeyBinding, butBindGauche, butBindDroite, butBindSaut,
    butCredit,
    butRetourOptions;
    Select butChoixRes;
    Switch fullScreen;

    void initButton();
    void input();
    void tick();
    void render();
    void drawBaseOptions();
    void drawGraphicOptions();
    void drawSoundsOptions();
    void drawKeyboardOptions();
    void drawCredit();
    void setScreenSize();
    void setScreenMode();
    char * drawKeyBind(int key);

public:
    Menu(SDL_Window *window, SDL_Renderer *renderer, int winW, int winH);
    ~Menu();

    bool start();
};


#endif //RTB_MENU_H
