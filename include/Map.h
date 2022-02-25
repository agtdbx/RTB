//
// Created by auguste on 23/02/2022.
//

#ifndef RTB_MAP_H
#define RTB_MAP_H

#include <iostream>
#include <vector>
#include "../include/Tuile.h"


class Map {
private:
    std::vector<std::vector<Tuile>> map;
    int w, h, startX, startY, endX, endY, squareSize;

public:
    Map();
    Map(int w, int h);
    ~Map();

    void draw(SDL_Renderer *renderer, Camera camera);
    Tuile get(int x, int y);
    int getSquarreSize();
    int getStartX();
    int getStartY();
    int getEndX();
    int getEndY();
};


#endif //RTB_MAP_H
