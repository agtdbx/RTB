//
// Created by auguste on 31/01/2022.
//

#include "../include/Button.h"

#include <SDL.h>
#include "../include/Functions.h"

//Private methods


//Public methods
Button::Button() {

}

Button::Button(char *text, int textSize, int x, int y, int width, int height, SDL_Color colorOff, SDL_Color colorOn) {
    this->text = text;
    this->textSize = textSize;
    this->x = x;
    this->y = y;
    this->w = width;
    this->h = height;
    this->colorOff = colorOff;
    this->colorOn = colorOn;
}


Button::~Button() {

}


void Button::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, this->colorOff.r, this->colorOff.g, this->colorOff.b, this->colorOff.a);
    SDL_Rect rect = {this->x, this->y, this->w, this->h}; // Création du carré (x, y, width, height)
    SDL_RenderFillRect(renderer, &rect); // Dessin du carré
    SDL_Color color = {0, 0, 0, 255};
    drawText(renderer, this->text, this->textSize, this->x + this->w/2, this->y, 1, color);
}