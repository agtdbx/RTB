//
// Created by auguste on 31/05/22.
//

#ifndef EDITEUR_RTB_MAP_H
#define EDITEUR_RTB_MAP_H

#include <iostream>
#include <vector>
#include "../include/Tuile.h"
#include "../include/Zone.h"
#include <SDL_image.h>

class Map {
private:
    std::vector<Zone> checkpoints;
    std::vector<std::vector<Tuile>> map;
    int w, h, squareSize;
    Zone start, end;

    void initEmptyMap(SDL_Renderer *renderer);
    std::vector<std::vector<Tuile>> copyMap();

public:
    Map();
    Map(int w, int h, int squareSize, SDL_Renderer *renderer);
    ~Map();

    void draw(SDL_Renderer *renderer, Camera camera, int winW, int winH);
    Tuile get(int x, int y);
    bool test(int x, int y, char direction);
    int touch(int x, int y);
    int getSquarreSize();
    void setStart(Zone start, SDL_Renderer *renderer);
    Zone getStart();
    void setEnd(Zone end, SDL_Renderer *renderer);
    Zone getEnd();
    int getWidth();
    int getHeigth();
    std::vector<Zone> getCheckpoint();
    Zone *testCheckpoint(float x, float y, int w, int h);
    void set(int x, int y, Tuile t);
    void addCheckpoint(Zone checkpoint);
    void removeCheckpoint(int id);
};


#endif //EDITEUR_RTB_MAP_H
