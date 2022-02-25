//
// Created by auguste on 23/02/2022.
//

#include "../include/Map.h"
#include <SDL.h>
#include <iostream>
#include <vector>
#include "../include/Tuile.h"


//private methods


//public methods
Map::Map() {
    this->squareSize = 20;
    this->w = 1920/this->squareSize;
    this->h = 1080/this->squareSize;
    this->startX = 100;
    this->startY = 100;
    this->endX = 200;
    this->endY = 200;
}

Map::Map(int w, int h) {
    this->w = w;
    this->h = h;
    this->startX = 100;
    this->startY = 100;
    this->endX = 200;
    this->endY = 200;
    this->squareSize = 20;

    SDL_Color black = {0, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};

    for (int i = 0; i < this->w; ++i){
        std::vector<Tuile> vector;
        for (int j = 0; j < this->h; ++j){
            Tuile tuile;
            if (i == 0 || i == this->w-1 || j == 0 || j == this->h-1){
                tuile = Tuile(i*this->squareSize, j*this->squareSize, this->squareSize, false, black);
            }
            else{
                tuile = Tuile(i*this->squareSize, j*this->squareSize, this->squareSize, true, white);
            }
            vector.push_back(tuile);
        }
        this->map.push_back(vector);
    }
}


Map::~Map() {

}


void Map::draw(SDL_Renderer *renderer, Camera camera) {
    for (int i = 0; i < this->w; ++i) {
        for (int j = 0; j < this->h; ++j) {
            this->map[i][j].draw(renderer, camera);
        }
    }
}


Tuile Map::get(int x, int y) {
    return this->map[x][y];
}

int Map::getSquarreSize() {
    return this->squareSize;
}

int Map::getStartX() {
    return this->startX;
}

int Map::getStartY() {
    return this->startY;
}

int Map::getEndX() {
    return this->endX;
}

int Map::getEndY() {
    return this->endY;
}