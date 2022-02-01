//
// Created by auguste on 01/02/2022.
//

#ifndef RTB_SELECT_H
#define RTB_SELECT_H

#include <SDL.h>
#include <iostream>
#include <vector>

class Select {
private:
    int x, y, w, h, textSize, textAlign,  mouseOver;
    char *text;
    std::vector<char*> values;
    bool extend;
    SDL_Color colorOff, colorOn;

    void mouseOnButton();
    void clicOnButton();

public:
    Select();
    Select(char *text, int textSize, int textAlign, int x, int y, int width, int height, SDL_Color colorOff, SDL_Color colorOn, std::vector<char*> values);
    ~Select();

    void draw(SDL_Renderer *renderer);
    int getValue();
};


#endif //RTB_SELECT_H
