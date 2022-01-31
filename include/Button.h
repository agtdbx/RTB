//
// Created by auguste on 31/01/2022.
//

#ifndef RTB_BUTTON_H
#define RTB_BUTTON_H

#include <SDL.h>

class Button {
private:
    int x, y, w, h, textSize;
    char *text;
    bool mouseOver;
    SDL_Color colorOff, colorOn;

    void mouseOnButton();

public:
    Button();
    Button(char *text, int textSize, int x, int y, int width, int height, SDL_Color colorOff, SDL_Color colorOn);
    ~Button();

    void draw(SDL_Renderer *renderer);
    bool clicOnButton();
};


#endif //RTB_BUTTON_H
