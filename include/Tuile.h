//
// Created by auguste on 23/02/2022.
//

#ifndef RTB_TUILE_H
#define RTB_TUILE_H

#include <SDL.h>
#include "../include/Camera.h"

class Tuile {
private:
    int x, y, size;
    bool passable;
    SDL_Color color;

public:
    Tuile();
    Tuile(int x, int y, int size, bool passable, SDL_Color color);
    ~Tuile();

    void draw(SDL_Renderer *renderer, Camera camera);
    bool isPassable();
};


#endif //RTB_TUILE_H
