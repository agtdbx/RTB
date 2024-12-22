//
// Created by auguste on 22/02/2022.
//

#ifndef RTB_PERSONNAGE_H
#define RTB_PERSONNAGE_H

#include <SDL.h>
#include "../include/Camera.h"
#include "../include/Map.h"
#include "../include/Background.h"

class Personnage {
private:
    int w, h;
    float x, y, vX, vY,
    vitesse, acceleration, speedModifier, nageAcceleration, nageVitesse,
    debutSaut, tempsSaut, graviteEffet, debutWallJump, timeOfChargeWallJump,
    respawnX, respawnY;
    bool sautOk, wallJumpOk, inWater;
    char viewDir, dirWallJump;
    SDL_Texture *sprite;

    bool isOnTuile(Map *map, std::string nomTuile, float x, float y);
    bool isInTuile(Map *map, std::string nomTuile, float x, float y);
    bool isInTuileWater(Map *map, std::string nomTuile, float x, float y);
    bool inAir(Map *map);
    bool canWallJump(Map *map);
    bool mouvementPossibleX(Map *map, float delta);
    bool mouvementPossibleY(Map *map, float delta);
    bool nagePossibleX(Map *map, float delta);
    bool nagePossibleY(Map *map, float delta);

public:
    Personnage();
    Personnage(float x, float y, int squareSize, SDL_Renderer *renderer);
    ~Personnage();

    void draw(SDL_Renderer *renderer, Camera camera);
    void deplacementX(char direction, Map *map);
    void addVx(float vX);
    void deplacementY(float vY);
    void addVy(float vY);
    void nageX(char direction);
    void nageY(char direction);
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
    bool isInWater(Map *map);
};


#endif //RTB_PERSONNAGE_H
