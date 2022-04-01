//
// Created by auguste on 23/02/2022.
//

#include "../include/Map.h"
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "../include/Tuile.h"
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <SDL2/SDL_image.h>

//private methods
void Map::getpixel(Pixel *pixel, SDL_Surface *surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    Uint8 red = p[3];
    Uint8 green = p[2];
    Uint8 blue = p[1];
    Uint8 alpha = p[0];

    pixel->r = red;
    pixel->g = green;
    pixel->b = blue;
    pixel->a = alpha;
}



void Map::loadMap(int lvl_num) {
    // Lecture du fichier json
    Json::Value json;
    std::ifstream myfile ("../data/levels/lvl_1.json");// Ouverture du fichier
    myfile >> json;

    // Assignation des valeurs du json
    this->w = json["width"].asInt();
    this->h = json["height"].asInt();
    this->startX = json["startX"].asInt()*20;
    this->startY = json["startY"].asInt()*20;
    this->endX = json["endX"].asInt()*20;
    this->endY = json["endY"].asInt()*20;
    std::string png_map = json["map_file"].asString();
    Json::Value special_tiles = json["special_tiles"];

    // Lecture du fichier png
    SDL_Surface* picture = IMG_Load("../data/levels/lvl_1.png");
    SDL_Surface* map = SDL_ConvertSurfaceFormat(picture, SDL_PIXELFORMAT_ABGR32, 0);

    // Création de la map avec les valeurs du png
    this->map.clear();
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color color = {255, 255, 255, 255};
    Pixel pixel;
    for (int i = 0; i < this->w; ++i){
        std::vector<Tuile> vector;
        for (int j = 0; j < this->h; ++j){
            this->getpixel(&pixel, map, i, j);
            if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0){
                Tuile tuile = Tuile(i*this->squareSize, j*this->squareSize, this->squareSize, "mur", black);
                vector.push_back(tuile);
            }
            else{
                color.r = pixel.r;
                color.g = pixel.g;
                color.b = pixel.b;
                color.a = pixel.a;
                if (color.r == 0 && color.g == 255 && color.b == 0){
                    Tuile tuile = Tuile(i*this->squareSize, j*this->squareSize, this->squareSize, "slime", color);
                    vector.push_back(tuile);
                }
                else if (color.r == 0 && color.g == 255 && color.b == 255){
                    Tuile tuile = Tuile(i*this->squareSize, j*this->squareSize, this->squareSize, "glace", color);
                    vector.push_back(tuile);
                }
                else if (color.r == 100 && color.g == 100 && color.b == 100){
                    Tuile tuile = Tuile(i*this->squareSize, j*this->squareSize, this->squareSize, "pique", color);
                    vector.push_back(tuile);
                }
                else{
                    Tuile tuile = Tuile(i*this->squareSize, j*this->squareSize, this->squareSize, "air", color);
                    vector.push_back(tuile);
                }
            }
        }
        this->map.push_back(vector);
    }
    SDL_FreeSurface(picture);
}


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

Map::Map(int nb) {
    this->w = 20;
    this->h = 20;
    this->startX = 2*20;
    this->startY = 15*20;
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
                tuile = Tuile(i*this->squareSize, j*this->squareSize, this->squareSize, "mur", black);
            }
            else{
                tuile = Tuile(i*this->squareSize, j*this->squareSize, this->squareSize, "air", white);
            }
            vector.push_back(tuile);
        }
        this->map.push_back(vector);
    }
    this->loadMap(1);
}


Map::~Map() {

}


void Map::draw(SDL_Renderer *renderer, Camera camera, int winW, int winH) {
    for (int i = 0; i < this->w; ++i) {
        for (int j = 0; j < this->h; ++j) {
            if (-20 <= i*20 - camera.getX() && i*20 - camera.getX() <= winW && -20 <= j*20 - camera.getY() && j*20 - camera.getY() <= winH){
                this->map[i][j].draw(renderer, camera);
            }
        }
    }
}


Tuile Map::get(int x, int y) {
    return this->map[x][y];
}

bool Map::test(int x, int y) {
    return this->map[x][y].isPassable();
}

int Map::touch(int x, int y) {
    return this->map[x][y].touch();
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