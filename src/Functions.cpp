//
// Created by auguste on 31/01/2022.
//

#include "../include/Functions.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

void drawText(SDL_Renderer *renderer , char *text, int textSize, int x, int y, int alignement, SDL_Color color){
    TTF_Font * font = 0;
    font = TTF_OpenFont("./data/fonts/Roboto-Regular.ttf", textSize);
    if (font != 0){
        SDL_Surface * surface = TTF_RenderText_Blended(font, text, color);
        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect position;
        position.y = y;
        position.w = surface->w;
        position.h = surface->h;
        if (alignement == 1){
            position.x = x - surface->w/2;
        }
        else if (alignement == 2){
            position.x = x - surface->w/2;
            position.y = y + surface->h/2;
        }
        else if (alignement == 3){
            position.x = x - surface->w;
        }
        else{
            position.x = x;
        }
        SDL_RenderCopy(renderer, texture, NULL, &position);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }
    else
        std::cout << "Marche po : " << SDL_GetError() << std::endl;
    TTF_CloseFont(font);
}


void drawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius){
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

SDL_Texture *getTexture(SDL_Renderer *renderer, std::string spritename)
{
    std::string path = "./data/sprites/";
    path.append(spritename);
    path.append(".png");
    char *img = const_cast<char*>(path.c_str());
    SDL_Surface *surface = IMG_Load(img);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}