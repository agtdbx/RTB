//
// Created by auguste on 31/01/2022.
//

#ifndef RTB_BUTTON_H
#define RTB_BUTTON_H

#include <SDL2/SDL.h>

class Button {
private:
    int x, y, w, h, textSize, textAlign, borderSize;
    char *text;
    bool mouseOver;
    SDL_Color textColor, colorOff, colorOn, borderColor;

    void mouseOnButton();

public:
    Button();
    Button(char *text, int textSize, int textAlign, SDL_Color textColor, int x, int y, int width, int height, SDL_Color colorOff, SDL_Color colorOn, int borderSize, SDL_Color borderColor);
    ~Button();

    void draw(SDL_Renderer *renderer);
    bool clicOnButton();
    void setX(int x);
    void setY(int y);
    void setColors(SDL_Color colorOff, SDL_Color colorOn, SDL_Color textColor, SDL_Color borderColor);
};


#endif //RTB_BUTTON_H
