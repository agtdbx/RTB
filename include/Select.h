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
    int x, y, w, h, textSize, textAlign,  mouseOver, borderSize;
    char *text;
    std::vector<char*> values;
    bool extend;
    SDL_Color colorOff, colorOn, borderColor;

    void mouseOnButton();
    void clicOnButton();

public:
    Select();
    Select(char *text, int textSize, int textAlign, int x, int y, int width, int height, SDL_Color colorOff, SDL_Color colorOn, std::vector<char*> values, int borderSize, SDL_Color borderColor);
    ~Select();

    void draw(SDL_Renderer *renderer);
    char* getValue();
};


#endif //RTB_SELECT_H