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
    this->x += this->vX * delta;
    this->y += this->vY * delta;
    camera.addPos(this->vX * delta, this->vY * delta);
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