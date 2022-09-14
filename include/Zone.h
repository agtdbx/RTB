//
// Created by auguste on 09/08/22.
//

#ifndef EDITEUR_RTB_ZONE_H
#define EDITEUR_RTB_ZONE_H


#include <string>
#include "SDL.h"
#include "../include/Camera.h"

class Zone {
private:
    int x, y, w, h, id, squareSize;
    SDL_Color color;
    SDL_Texture *sprite;

public:
    Zone();
    Zone(int x, int y, std::string type, int squareSize, SDL_Renderer *renderer);
    Zone(int x, int y, int id, int squareSize, SDL_Renderer *renderer);
    ~Zone();

    void draw(SDL_Renderer *renderer, Camera camera);
    bool inZone(int x, int y);
    int getX();
    int getY();
    int getId();
    void setId(int id);
};


#endif //EDITEUR_RTB_ZONE_H
