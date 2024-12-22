//
// Created by auguste on 13/09/22.
//

#ifndef RTB_BACKGROUND_H
#define RTB_BACKGROUND_H

#include <SDL.h>

class Background {
private:
    int fenW, fenH;
    float camX, camY;
    SDL_Texture *sprite;

public:
    Background();
    Background(SDL_Renderer *renderer, int fenW, int fenH);
    ~Background();

    void addCamX(float value);
    void addCamY(float value);
    void draw(SDL_Renderer *renderer);
};


#endif //RTB_BACKGROUND_H
