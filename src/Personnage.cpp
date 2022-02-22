//
// Created by auguste on 22/02/2022.
//

#include "../include/Personnage.h"
#include <SDL.h>


// Private methodes


// Public methodes
Personnage::Personnage() {
    this->x = 50.0f;
    this->y = 50.0f;
    this->w = 40;
    this->h = 60;
    this->vX = 0.0f;
    this->vY= 0.0f;
}


Personnage::Personnage(float x, float y) {
    this->x = x;
    this->y = y;
    this->w = 40;
    this->h = 60;
    this->vX = 0.0f;
    this->vY= 0.0f;
}


Personnage::~Personnage() {

}


void Personnage::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
    int x = this->x;
    int y = this->y;
    SDL_Rect rect = {x, y, this->w, this->h};
    SDL_RenderFillRect(renderer, &rect);
}