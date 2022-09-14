//
// Created by auguste on 25/02/2022.
//

#include <iostream>
#include "../include/Camera.h"


//Private methods


//Public methods
Camera::Camera() {
    this->x = 0.0f;
    this->y = 0.0f;
    this->winW = 1920.0f;
    this->winH = 1080.0f;
    this->mapW = 19.0f;
    this->mapH = 11.0f;
}


Camera::~Camera() {

}


float Camera::getX() {
    return this->x;
}


float Camera::getY() {
    return this->y;
}


void Camera::tick(float x, float y, float vX, float vY, int w, int h, Background *background) {
    this->x = x - (this->winW / 2);
    this->y = y - (this->winH / 2);

    if (this->x < 0.0f || this->mapW * this->mapSize <= this->winW) {
        this->x = 0.0f;
        vX = 0.0f;
    }
    else if (this->x + this->winW > this->mapW * this->mapSize) {
        this->x = (this->mapW * this->mapSize) - this->winW;
        vX = 0.0f;
    }

    if (this->y < 0.0f || this->mapH * this->mapSize <= this->winH) {
        this->y = 0.0f;
        vY = 0.0f;
    }
    else if (this->y + this->winH > this->mapH * this->mapSize){
        this->y = (this->mapH * this->mapSize) - this->winH;
        vY = 0.0f;
    }

    background->addCamX(vX / 300.0f);
    background->addCamY(vY / 300.0f);
}


void Camera::setWindowSize(float w, float h) {
    this->winW = w;
    this->winH = h;
}


void Camera::setMapSize(float w, float h, float size) {
    this->mapW = w;
    this->mapH = h;
    this->mapSize = size;
}