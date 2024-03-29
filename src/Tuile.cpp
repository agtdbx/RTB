//
// Created by auguste on 31/05/22.
//

#include <iostream>
#include <string>
#include "../include/Tuile.h"
#include "../include/Functions.h"


// private methodes



// public methodes
Tuile::Tuile() {
    this->x = 0;
    this->y = 0;
    this->size = 10;
    this->type = "mur";
    this->color = {100, 100, 100, 255};
}


Tuile::Tuile(int x, int y, int size, std::string type, SDL_Renderer *renderer) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->type = type;
    this->sprite = getTexture(renderer, this->type);

    /*if (this->type == "mur")
        this->color = {0, 0, 0, 255};
    else if (this->type == "air")
        this->color = {255, 255, 255, 255};
    else if (this->type == "slime")
        this->color = {0, 255, 0, 255};
    else if (this->type == "glace")
        this->color = {0, 255, 255, 255};
    else if (this->type == "pique")
        this->color = {255, 0, 0, 255};
    else if (this->type == "plateforme")
        this->color = {100, 100, 100, 255};
    else if (this->type == "eau")
        this->color = {50, 50, 255, 255};*/
}


Tuile::~Tuile() {

}


void Tuile::draw(SDL_Renderer *renderer, Camera camera) {
    if (this->type != "air")
    {
        //SDL_SetRenderDrawColor(renderer, this->color.r, this->color.g, this->color.b, this->color.a);
        int x = this->x*this->size - camera.getX();
        int y = this->y*this->size  - camera.getY();
        SDL_Rect pos = {x, y, this->size, this->size};
        //SDL_RenderFillRect(renderer, &rect);
        SDL_RenderCopy(renderer, this->sprite, NULL, &pos);
    }
}


bool Tuile::isPassable(char direction) {
    if (this->type == "air" || this->type == "pique" || this->type == "eau" || (this->type == "plateforme" && direction != 'D')) {
        return true;
    }
    return false;
}


int Tuile::touch() {
    if (this->type == "mur")
        return 0;
    if (this->type == "air")
        return 1;
    if (this->type == "slime")
        return 2;
    if (this->type == "glace")
        return 3;
    if (this->type == "pique")
        return 4;
    if (this->type == "plateforme")
        return 5;
    if (this->type == "eau")
        return 6;
    return -1;
}


std::string Tuile::getType() {
    return this->type;
}


SDL_Color Tuile::getColor() {
    return this->color;
}