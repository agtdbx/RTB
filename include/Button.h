//
// Created by auguste on 31/01/2022.
//

#ifndef RTB_BUTTON_H
#define RTB_BUTTON_H

#include <SDL.h>
#include <iostream>

class Button {
private:
    int x, y, width, height;
    std::string text;

public:
    Button(char *text, int x, int y, int width, int height);
    ~Button();

    void draw(SDL_Renderer *renderer);
};


#endif //RTB_BUTTON_H
