//
// Created by auguste on 23/02/2022.
//

#ifndef RTB_TUILE_H
#define RTB_TUILE_H

#include <SDL.h>
#include "../include/Camera.h"

class Tuile {
protected:
    int x, y, size;
    std::string type;
    SDL_Color color;

public:
    Tuile();
    Tuile(int x, int y, int size, std::string type, SDL_Color color);
    ~Tuile();

    void draw(SDL_Renderer *renderer, Camera camera);
    bool isPassable();
    int touch();
};


#endif //RTB_TUILE_H
