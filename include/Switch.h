//
// Created by auguste on 02/02/2022.
//

#ifndef RTB_SWITCH_H
#define RTB_SWITCH_H

#include <SDL.h>

class Switch {
private:
    int x, y, w, h, borderSize;
    float lastClic;
    bool active, mouseOver;
    SDL_Color colorOff, colorOn, borderColor;
    void mouseOnButton();
    void clicOnButton();

public:
    Switch();
    Switch(int x, int y, int w, int h, SDL_Color colorOff, SDL_Color colorOn, int borderSize, SDL_Color borderColor);
    ~Switch();
    void draw(SDL_Renderer *renderer);
    bool isActive();
};


#endif //RTB_SWITCH_H
