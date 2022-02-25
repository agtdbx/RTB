//
// Created by auguste on 22/02/2022.
//

#ifndef RTB_PERSONNAGE_H
#define RTB_PERSONNAGE_H

#include <SDL.h>
#include "../include/Camera.h"
#include "../include/Map.h"

class Personnage {
private:
    int w, h;
    float x, y, vX, vY, vitesse, acceleration;

    bool mouvementPossibleX(Camera camera, Map map, float delta);
    bool mouvementPossibleY(Camera camera, Map map, float delta);

public:
    Personnage();
    Personnage(float x, float y);
    ~Personnage();

    void draw(SDL_Renderer *renderer, Camera camera);
    void deplacementX(float vX);
    void addVx(float vX);
    void stopVx();
    void deplacementY(float vY);
    void addVy(float vY);
    void stopVy();
    void move(float delta, Camera& camera, Map map);
    float getAcceleration();
    float getX();
    float getY();
    int getWidth();
    int getHeight();
};


#endif //RTB_PERSONNAGE_H
