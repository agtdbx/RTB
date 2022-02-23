//
// Created by auguste on 22/02/2022.
//

#ifndef RTB_PERSONNAGE_H
#define RTB_PERSONNAGE_H

#include <SDL.h>

class Personnage {
private:
    int w, h;
    float x, y, vX, vY, vitesse, acceleration;

public:
    Personnage();
    Personnage(float x, float y);
    ~Personnage();

    void draw(SDL_Renderer *renderer);
    void addVx(float vX);
    void stopVx();
    void addVy(float vY);
    void move(float delta);
    float getAcceleration();
};


#endif //RTB_PERSONNAGE_H
