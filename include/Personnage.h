//
// Created by auguste on 22/02/2022.
//

#ifndef RTB_PERSONNAGE_H
#define RTB_PERSONNAGE_H

#include <SDL2/SDL.h>
#include "../include/Camera.h"
#include "../include/Map.h"
#include "../include/Background.h"

class Personnage {
private:
    int w, h;
    float x, y, vX, vY, vitesse, acceleration, debutSaut, tempsSaut, respawnX, respawnY, graviteEffet, speedModifier, debutWallJump, timeOfChargeWallJump;
    bool sautOk, wallJumpOk;
    char viewDir, dirWallJump;
    SDL_Texture *sprite;

    bool isOnTuile(Map *map, std::string nomTuile, float x, float y);
    bool isInTuile(Map *map, std::string nomTuile, float x, float y);
    bool inAir(Map *map);
    bool canWallJump(Map *map);
    bool mouvementPossibleX(Map *map, float delta);
    bool mouvementPossibleY(Map *map, float delta);

public:
    Personnage();
    Personnage(float x, float y, int squareSize, SDL_Renderer *renderer);
    ~Personnage();

    void draw(SDL_Renderer *renderer, Camera camera);
    void deplacementX(char direction, Map *map);
    void addVx(float vX);
    void deplacementY(float vY);
    void addVy(float vY);
    bool saut(Map *map, bool space_pressed);
    bool walljump(Map *map, bool space_pressed);
    void move(float delta, Camera& camera, Map *map);
    float getX();
    float getY();
    float getVx();
    float getVy();
    int getWidth();
    int getHeight();
    bool atFin(Map *map);
    void respawn();
    void setRespawn(float x, float y);
    bool isMort(Map *map);
};


#endif //RTB_PERSONNAGE_H
