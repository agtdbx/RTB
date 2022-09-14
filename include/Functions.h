//
// Created by auguste on 31/01/2022.
//

#ifndef RTB_FUNCTIONS_H
#define RTB_FUNCTIONS_H

#include <SDL.h>
#include <string>

void drawText(SDL_Renderer *renderer , char *text, int textSize, int x, int y, int alignement, SDL_Color color);

void drawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius);

SDL_Texture *getTexture(SDL_Renderer *renderer, std::string spritename);

#endif //RTB_FUNCTIONS_H
