//
// Created by auguste on 25/02/2022.
//

#include <iostream>
#include "../include/Camera.h"


//Private methods
void Camera::avoidOutOfMap() {
    /*std::cout << "from " << this->x << ", " << this->y;
    if (this->x < 0)
        this->x = 0;
    if (this->x + this->winW > this->mapW * 20)
        this->x = (this->mapW * 20) - this->winW;

    if (this->y < 0)
        this->y = 0;
    if (this->y + this->winH > this->mapH * 20)
        this->y = (this->mapH * 20) - this->winH;

    std::cout << " to " << this->x << ", " << this->y << std::endl;*/
}


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


void Camera::addPosX(float x) {
    this->x += x;
    this->avoidOutOfMap();
}


void Camera::addPosY(float y) {
    this->y += y;
    this->avoidOutOfMap();
}


void Camera::setPos(float x, float y) {
    this->x = x;
    this->y = y;
    this->avoidOutOfMap();
}


void Camera::setWindowSize(float w, float h) {
    this->winW = w;
    this->winH = h;
}


void Camera::setMapSize(float w, float h) {
    this->mapW = w;
    this->mapH = h;
}

void Camera::linkToPerso(Personnage *perso) {
    this->perso = perso;
}