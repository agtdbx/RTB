//
// Created by auguste on 29/01/2022.
//

#ifndef RTB_MENU_H
#define RTB_MENU_H

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "../include/Button.h"
#include "../include/Select.h"
#include "../include/Switch.h"

class Menu {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int winW, winH, fenetre, spacingWithScreen, borderSize,
    volumeMusique, volumeSon,
    toucheHaut, toucheBas, toucheGauche, toucheDroite, toucheSaut,
    lastLevelComplete, nb_levels, levelLoad;
    float lastClic, lastTime;
    bool run, continuer;
    char toucheABind;
    std::vector<Button> butlvls;
    Button butJouer, butOptions, butQuitter,
    butRetourJouer,
    butGraphics,
    butSonore, butMusiqueMoins, butMusiquePlus, butSonMoins, butSonPlus,
    butKeyBinding, butBindHaut, butBindBas, butBindGauche, butBindDroite, butBindSaut,
    butCredit,
    butRetourOptions;
    Select butChoixRes;
    Switch fullScreen;
    SDL_Color color, textColor;
    SDL_Texture *background;
    Mix_Music *menu_theme;
    Mix_Chunk *button_clic_sound;

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
    void saveOptions();
    void loadOptions();

public:
    Menu(SDL_Window *window, SDL_Renderer *renderer, int winW, int winH);
    ~Menu();

    bool start();
    int getNumLevel();
    int getVolumeSon();
    int getVolumeMusique();
    int getToucheHaut();
    int getToucheBas();
    int getToucheGauche();
    int getToucheDroite();
    int getToucheSaut();
    int getWinWidth();
    int getWinHeight();
    void setLastLevelComplete(int level);
};


#endif //RTB_MENU_H
