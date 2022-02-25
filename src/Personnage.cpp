//
// Created by auguste on 22/02/2022.
//

#include "../include/Personnage.h"
#include <SDL.h>


// Private methodes

bool Personnage::mouvementPossibleX(Camera camera, Map map, float delta) {
    int x1 = (this->x + this->vX*delta)/20;
    int x2 = (this->x + this->w/2 + this->vY*delta)/20;
    int x3 = (this->x + this->w + this->vY*delta)/20;
    int y1 = (this->y)/20;
    int y2 = (this->y + this->h/2)/20;
    int y3 = (this->y + this->h)/20;

    if (map.test(x1, y1) && map.test(x1, y2) && map.test(x1, y3) &&
        map.test(x2, y1) && map.test(x2, y2) && map.test(x2, y3) &&
        map.test(x3, y1) && map.test(x3, y2) && map.test(x3, y3)){;
        return true;
    }
    return false;
}


bool Personnage::mouvementPossibleY(Camera camera, Map map, float delta) {
    int x1 = (this->x)/20;
    int x2 = (this->x + this->w/2)/20;
    int x3 = (this->x + this->w)/20;
    int y1 = (this->y + this->vY*delta)/20;
    int y2 = (this->y + this->h/2 + this->vY*delta)/20;
    int y3 = (this->y + this->h + this->vY*delta)/20;

    if (map.test(x1, y1) && map.test(x1, y2) && map.test(x1, y3) &&
        map.test(x2, y1) && map.test(x2, y2) && map.test(x2, y3) &&
        map.test(x3, y1) && map.test(x3, y2) && map.test(x3, y3)){;
        return true;
    }
    return false;
}


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
    this->vitesse = 500.0f;
    this->acceleration = 50.0f;
}


Personnage::~Personnage() {

}


void Personnage::draw(SDL_Renderer *renderer, Camera camera) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
    int x = this->x - camera.getX();
    int y = this->y - camera.getY();
    SDL_Rect rect = {x, y, this->w, this->h};
    SDL_RenderFillRect(renderer, &rect);
}


void Personnage::deplacementX(float vX) {
    this->vX += vX;
    if (this->vX > this->vitesse){
        this->vX = this->vitesse;
    }
    else if (this->vX < -this->vitesse){
        this->vX = -this->vitesse;
    }
}


void Personnage::addVx(float vX) {
    this->vX += vX;
}


void Personnage::stopVx() {
    this->vX = 0.0f;
}


void Personnage::deplacementY(float vY) {
    this->vY += vY;
    if (this->vY > this->vitesse){
        this->vY = this->vitesse;
    }
    else if (this->vY < -this->vitesse){
        this->vY = -this->vitesse;
    }
}


void Personnage::addVy(float vY) {
    this->vY += vY;
}


void Personnage::stopVy() {
    this->vY = 0.0f;
}


void Personnage::move(float delta, Camera& camera, Map map) {
    if (this->mouvementPossibleX(camera, map, delta)){
        this->x += this->vX * delta;
        camera.addPosX(this->vX * delta);
    }
    if (this->mouvementPossibleY(camera, map, delta)){
        this->y += this->vY * delta;
        camera.addPosY(this->vY * delta);
    }
}


float Personnage::getAcceleration() {
    return this->acceleration;
}


float Personnage::getX() {
    return this->x;
}


float Personnage::getY() {
    return this->y;
}


int Personnage::getWidth() {
    return this->w;
}


int Personnage::getHeight() {
    return this->h;
}