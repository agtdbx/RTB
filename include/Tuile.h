//
// Created by auguste on 31/05/22.
//

#ifndef EDITEUR_RTB_TUILE_H
#define EDITEUR_RTB_TUILE_H

#include <SDL.h>
#include "../include/Camera.h"

class Tuile {
protected:
    int x, y, size;
    std::string type;
    SDL_Color color;
    SDL_Texture *sprite;

public:
    Tuile();
    Tuile(int x, int y, int size, std::string type, SDL_Renderer *renderer);
    ~Tuile();

    void draw(SDL_Renderer *renderer, Camera camera);
    bool isPassable(char direction);
    int touch();

    std::string getType();
    SDL_Color getColor();
};


#endif //EDITEUR_RTB_TUILE_H
