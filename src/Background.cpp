//
// Created by auguste on 13/09/22.
//

#include "../include/Background.h"
#include "../include/Functions.h"

//private methods


//public methods
Background::Background() {
    this->fenW = 1920;
    this->fenH = 1080;
    this->camX = 0.0f;
    this->camY = 0.0f;
    this->sprite = getTexture(NULL, "background");
}


Background::Background(SDL_Renderer *renderer, int fenW, int fenH) {
    this->fenW = fenW;
    this->fenH = fenH;
    this->camX = 0.0f;
    this->camY = 0.0f;
    this->sprite = getTexture(renderer, "background");
}


Background::~Background() {

}


void Background::addCamX(float value) {
    this->camX -= value;
    if (this->camX <= -320.0f)
        this->camX += 320.0f;
    else if (this->camX > 0.0f)
        this->camX = -320.0f;
}


void Background::addCamY(float value) {
    this->camY -= value;
    if (this->camY <= -320.0f)
        this->camY += 320.0f;
    else if (this->camY > 0.0f)
        this->camY = -320.0f;
}


void Background::draw(SDL_Renderer *renderer) {
    int x = 0;
    int y = 0;

    while (y <= this->fenH / 320 + 1)
    {
        x = 0;
        while (x <= this->fenW / 320 + 1)
        {
            SDL_Rect rect = {x * 320 + (int)this->camX, y * 320 + (int)this->camY, 320, 320};
            SDL_RenderCopy(renderer, this->sprite, NULL, &rect);
            x++;
        }
        y++;
    }
}