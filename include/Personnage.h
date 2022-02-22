//
// Created by auguste on 22/02/2022.
//

#ifndef RTB_PERSONNAGE_H
#define RTB_PERSONNAGE_H

#include <SDL.h>

class Personnage {
private:
    int w, h;
    float x, y, vX, vY;

public:
    Personnage();
    Personnage(float x, float y);
    ~Personnage();

    void draw(SDL_Renderer *renderer);
};


#endif //RTB_PERSONNAGE_H
