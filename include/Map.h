//
// Created by auguste on 23/02/2022.
//

#ifndef RTB_MAP_H
#define RTB_MAP_H

#include <iostream>
#include <vector>
#include "../include/Tuile.h"
#include <SDL_image.h>

struct Pixel{
    int r, g, b, a;
};
typedef struct Pixel Pixel;

class Map {
private:
    std::vector<std::vector<Tuile>> map;
    int w, h, startX, startY, endX, endY, squareSize;
    void getpixel(Pixel *pixel, SDL_Surface *surface, int x, int y);
    void loadMap(int lvl_num);

public:
    Map();
    Map(int nb);
    ~Map();

    void draw(SDL_Renderer *renderer, Camera camera, int winW, int winH);
    Tuile get(int x, int y);
    bool test(int x, int y);
    int getSquarreSize();
    int getStartX();
    int getStartY();
    int getEndX();
    int getEndY();
};


#endif //RTB_MAP_H
