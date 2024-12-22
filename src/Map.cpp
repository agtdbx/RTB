//
// Created by auguste on 31/05/22.
//

#include "../include/Map.h"
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "../include/Tuile.h"
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <SDL_image.h>

//private methods
void Map::initEmptyMap(SDL_Renderer *renderer) {
    this->map.clear();

    for (int i = 0; i < this->w; ++i){
        std::vector<Tuile> vector;
        for (int j = 0; j < this->h; ++j){
            Tuile tuile;
            if (i == 0 || i == this->w-1 || j == 0 || j == this->h-1){
                tuile = Tuile(i, j, this->squareSize, "mur", renderer);
            }
            else{
                tuile = Tuile(i, j, this->squareSize, "air", renderer);
            }
            vector.push_back(tuile);
        }
        this->map.push_back(vector);
    }
}


std::vector<std::vector<Tuile>> Map::copyMap() {
    std::vector<std::vector<Tuile>> copyMap;

    for (int x = 0; x < this->map.size(); x++){
        std::vector<Tuile> vector;
        for (int y = 0; y < this->map[0].size(); y++){
            vector.push_back(this->map[x][y]);
        }
        copyMap.push_back(vector);
    }

    return copyMap;
}


//public methods
Map::Map() {
    this->w = 32;
    this->h = 18;
    this->start = Zone(1, 1, "start", 30, NULL);
    this->end = Zone(3, 3, "end", 30, NULL);
    this->squareSize = 30;

    initEmptyMap(NULL);
}

Map::Map(int w, int h, int squareSize, SDL_Renderer *renderer) {
    this->w = w;
    this->h = h;
    this->start = Zone(1, 1, "start", squareSize, renderer);
    this->end = Zone(3, 3, "end", squareSize, renderer);
    this->squareSize = squareSize;

    initEmptyMap(renderer);
}


Map::~Map() {

}


void Map::draw(SDL_Renderer *renderer, Camera camera, int winW, int winH) {
    int minX = -this->squareSize;
    int minY = -this->squareSize;
    int maxX = (camera.getX() + winW) / this->squareSize + 1;
    int maxY = (camera.getY() + winH) / this->squareSize + 1;
    int x = camera.getX() / this->squareSize;
    while (x < maxX && x < this->w) {
        int y = camera.getY() / this->squareSize;
        while (y < maxY && y < this->h) {
            this->map[x][y].draw(renderer, camera);
            y++;
        }
        x++;
    }
    this->start.draw(renderer, camera);
    this->end.draw(renderer, camera);

    for (Zone check : this->checkpoints){
        check.draw(renderer, camera);
    }
}


Tuile Map::get(int x, int y) {
    if (x < 0 || x >= this->w)
        x = 0;
    if (y < 0 || y >= this->h)
        y = 0;
    return this->map[x][y];
}


bool Map::test(int x, int y, char direction) {
    if (x >= 0 && x < this->map.size() && y >= 0 && y < this->map[0].size()){
        return this->map[x][y].isPassable(direction);
    }
    return false;
}

int Map::touch(int x, int y) {
    if (x >= 0 && x < this->map.size() && y >= 0 && y < this->map[0].size()){
        return this->map[x][y].touch();
    }
    return 0;
}


int Map::getSquarreSize() {
    return this->squareSize;
}


void Map::setStart(Zone start, SDL_Renderer *renderer) {
    this->start = start;

    int x = start.getX();
    int y = start.getY();
    this->map[x][y] = Tuile(x, y, this->squareSize, "air", renderer);
    this->map[x+1][y] = Tuile(x+1, y, this->squareSize, "air", renderer);
    this->map[x][y+1] = Tuile(x, y+1, this->squareSize, "air", renderer);
    this->map[x+1][y+1] = Tuile(x+1, y+1, this->squareSize, "air", renderer);
    this->map[x][y+2] = Tuile(x, y+2, this->squareSize, "air", renderer);
    this->map[x+1][y+2] = Tuile(x+1, y+2, this->squareSize, "air", renderer);
}


Zone Map::getStart() {
    return this->start;
}


void Map::setEnd(Zone end, SDL_Renderer *renderer) {
    this->end = end;

    int x = end.getX();
    int y = end.getY();
    this->map[x][y] = Tuile(x, y, this->squareSize, "air", renderer);
    this->map[x+1][y] = Tuile(x+1, y, this->squareSize, "air", renderer);
    this->map[x][y+1] = Tuile(x, y+1, this->squareSize, "air", renderer);
    this->map[x+1][y+1] = Tuile(x+1, y+1, this->squareSize, "air", renderer);
    this->map[x][y+2] = Tuile(x, y+2, this->squareSize, "air", renderer);
    this->map[x+1][y+2] = Tuile(x+1, y+2, this->squareSize, "air", renderer);
}


Zone Map::getEnd() {
    return this->end;
}


Zone *Map::testCheckpoint(float x, float y, int w, int h) {
    Zone *rep = NULL;

    for (int i = 0; i < this->checkpoints.size(); i++){
        Zone *checkpoint = &this->checkpoints[i];
        if (checkpoint->getX()*this->squareSize <= (x + w) && (checkpoint->getX()*this->squareSize + 3*this->squareSize) >= x &&
            checkpoint->getY()*this->squareSize <= (y + h) && (checkpoint->getY()*this->squareSize + 3*this->squareSize) >= y){
            checkpoint->activate();
            rep = checkpoint;
        }
    }

    return rep;
}


int Map::getWidth() {
    return this->w;
}


int Map::getHeigth() {
    return this->h;
}


std::vector<Zone> Map::getCheckpoint() {
    return this->checkpoints;
}


void Map::set(int x, int y, Tuile t) {
    this->map[x][y] = t;
}


void Map::addCheckpoint(Zone checkpoint) {
    this->checkpoints.push_back(checkpoint);
}


void Map::removeCheckpoint(int id) {
    this->checkpoints.erase(this->checkpoints.cbegin() + id);

    for (int i = 0; i < this->checkpoints.size(); i++){
        this->checkpoints[i].setId(i);
    }
}
