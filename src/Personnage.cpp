//
// Created by auguste on 22/02/2022.
//

#include "../include/Personnage.h"
#include "../include/Functions.h"
#include <SDL2/SDL.h>


// Private methodes
bool Personnage::isOnTuile(Map *map, std::string nomTuile, float x, float y) {
    int x1 = (int)(x) / map->getSquarreSize();
    int x2 = (int)(x + this->w/2) / map->getSquarreSize();
    int x3 = (int)(x + this->w) / map->getSquarreSize();
    int y4 = (int)(y + this->h) / map->getSquarreSize();

    if (map->get(x1, y4).getType() == nomTuile || map->get(x2, y4).getType() == nomTuile || map->get(x3, y4).getType() == nomTuile)
        return true;
    return false;
}


bool Personnage::isOverTuile(Map *map, std::string nomTuile, float x, float y) {
    int x1 = (int)(x) / map->getSquarreSize();
    int x2 = (int)(x + this->w/2) / map->getSquarreSize();
    int x3 = (int)(x + this->w) / map->getSquarreSize();
    int y4 = (int)(y + this->h) / map->getSquarreSize() + 1;

    if (map->get(x1, y4).getType() == nomTuile || map->get(x2, y4).getType() == nomTuile || map->get(x3, y4).getType() == nomTuile)
        return true;
    return false;
}


bool Personnage::isInTuile(Map *map, std::string nomTuile, float x, float y) {
    int x1 = (int)(x) / map->getSquarreSize();
    int x2 = (int)(x + this->w/2) / map->getSquarreSize();
    int x3 = (int)(x + this->w) / map->getSquarreSize();
    int y1 = (int)(y) / map->getSquarreSize();
    int y2 = (int)(y + this->h/3) / map->getSquarreSize();
    int y3 = (int)(y + (this->h/3)*2) / map->getSquarreSize();
    int y4 = (int)(y + this->h) / map->getSquarreSize();

    if (map->get(x1, y1).getType() == nomTuile || map->get(x2, y1).getType() == nomTuile || map->get(x3, y1).getType() == nomTuile ||
        map->get(x1, y2).getType() == nomTuile || map->get(x2, y2).getType() == nomTuile || map->get(x3, y2).getType() == nomTuile ||
        map->get(x1, y3).getType() == nomTuile || map->get(x2, y3).getType() == nomTuile || map->get(x3, y3).getType() == nomTuile ||
        map->get(x1, y4).getType() == nomTuile || map->get(x2, y4).getType() == nomTuile || map->get(x3, y4).getType() == nomTuile)
            return true;
    return false;
}


bool Personnage::inAir(Map *map) {
    int x1 = (int)(this->x) / map->getSquarreSize();
    int x2 = (int)(this->x + this->w/2) / map->getSquarreSize();
    int x3 = (int)(this->x + this->w) / map->getSquarreSize();
    int y1 = (int)(this->y) / map->getSquarreSize();
    int y2 = (int)(this->y + this->h/3) / map->getSquarreSize();
    int y3 = (int)(this->y + (this->h/3)*2) / map->getSquarreSize();
    int y4 = (int)(this->y + this->h) / map->getSquarreSize();
    int y5 = (int)(y + this->h) / map->getSquarreSize() + 1;

    if (map->get(x1, y1).getType() == "air" && map->get(x2, y1).getType() == "air" && map->get(x3, y1).getType() == "air" &&
        map->get(x1, y2).getType() == "air" && map->get(x2, y2).getType() == "air" && map->get(x3, y2).getType() == "air" &&
        map->get(x1, y3).getType() == "air" && map->get(x2, y3).getType() == "air" && map->get(x3, y3).getType() == "air" &&
        map->get(x1, y4).getType() == "air" && map->get(x2, y4).getType() == "air" && map->get(x3, y4).getType() == "air" &&
        map->get(x1, y5).getType() == "air" && map->get(x2, y5).getType() == "air" && map->get(x3, y5).getType() == "air")
        return true;
    return false;
}

bool Personnage::canWallJump(Map *map) {
    int dirAdd = 0;

    if (this->vX < 0.0f)
        dirAdd = -1;
    else if (this->vX > 0.0f)
        dirAdd = 3;

    int x = (int)(this->x) / map->getSquarreSize() + dirAdd;
    int y4 = (int)(this->y + this->h) / map->getSquarreSize();

    if (map->get(x, y4).getType() == "mur")
        return true;
    return false;
}

bool Personnage::mouvementPossibleX(Map *map, float delta) {
    float x = this->x + (this->vX * delta);
    float y = this->y;

    if (this->isInTuile(map, "mur", x, y) || this->isInTuile(map, "glace", x, y))
    {
        this->vX = 0.0f;
        return false;
    }
    if (this->isInTuile(map, "slime", x, y))
        this->vX *= -1.0f;
    return true;
}


bool Personnage::mouvementPossibleY(Map *map, float delta) {
    float x = this->x;
    float y = this->y + (this->vY * delta);

    if (this->isInTuile(map, "slime", x, y))
        this->vY *= -1.0f;
    else if (this->isInTuile(map, "mur", x, y) || this->isInTuile(map, "glace", x, y) || (this->vY > 0.0f && this->isOnTuile(map, "plateforme", x, y)))
    {
        this->vY = 0.0f;
        return false;
    }

    return true;
}


// Public methodes
Personnage::Personnage() {
    this->x = 50.0f;
    this->y = 50.0f;
    this->w = 39;
    this->h = 59;
    this->vX = 0.0f;
    this->vY = 0.0f;
    this->respawnX = 50.0f;
    this->respawnY = 50.0f;
}


Personnage::Personnage(float x, float y,  int squareSize, SDL_Renderer *renderer) {
    this->respawnX = x;
    this->respawnY = y;
    this->x = x;
    this->y = y;
    this->w = 2 * squareSize - 1;
    this->h = 3 * squareSize - 1;
    this->vX = 0.0f;
    this->vY = 0.0f;
    this->vitesse = 500.0f;
    this->acceleration = 50.0f;
    this->debutSaut = 0.0f;
    this->tempsSaut = 0.1f;
    this->sautOk = false;
    this->graviteEffet = 1.0f;
    this->speedModifier = 1.0f;
    this->wallJumpOk = false;
    this->debutWallJump = 0.0f;
    this->timeOfChargeWallJump = 0.0f;
    this->viewDir = 'R';
    this->sprite = getTexture(renderer, "perso");
}


Personnage::~Personnage() {

}


void Personnage::draw(SDL_Renderer *renderer, Camera camera) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 200, 50);
    int x = this->x - camera.getX();
    int y = this->y - camera.getY();
    SDL_Rect part = {0, 0, 60, 90};
    if (this->viewDir == 'L')
        part = {70, 0, 60, 90};
    SDL_Rect pos = {x, y, this->w, this->h};
    SDL_RenderCopy(renderer, this->sprite, &part, &pos);
}


void Personnage::deplacementX(char direction, Map *map) {
    if (this->isOverTuile(map, "glace", this->x, this->y))
        this->speedModifier = 1.3f;
    else if (this->isInTuile(map, "eau", this->x, this->y))
        this->speedModifier = 0.7f;
    else if (!this->inAir(map))
        this->speedModifier = 1.0f;

    if (direction == 'g'){
        this->vX = -this->vitesse * this->speedModifier;
        this->viewDir = 'L';
    }
    else if (direction == 'd'){
        this->vX = this->vitesse * this->speedModifier;
        this->viewDir = 'R';
    }
    else {
        float frotement = 0.0f;
        if (this->isOverTuile(map, "glace", this->x, this->y))
            frotement = 10.0f;
        else if (this->inAir(map))
            frotement = 40.0f;
        else if (this->isInTuile(map, "eau", this->x, this->y))
            frotement = 80.0f;
        if (frotement != 0.0f)
        {
            if (this->vX >= frotement)
                this->vX -= frotement;
            else if (this->vX <= -frotement)
                this->vX += frotement;
            else
                this->vX = 0.0f;
        }
        else
            this->vX = 0.0f;
    }
    if (this->vX > this->vitesse * this->speedModifier)
        this->vX = this->vitesse * this->speedModifier;
    else if (this->vX < -this->vitesse * this->speedModifier)
        this->vX = -this->vitesse * this->speedModifier;
}


void Personnage::addVx(float vX) {
    this->vX += vX;
    if (this->vX > 1000.0f){
        this->vX = 1000.0f;
    }
}


void Personnage::deplacementY(float vY) {
    if (this->vY > this->vitesse){
        this->vY = this->vitesse;
    }
    else if (this->vY < -this->vitesse){
        this->vY = -this->vitesse;
    }
}


void Personnage::addVy(float vY) {
    if (this->vY > 1000.0f * this->graviteEffet)
        this->vY += (vY * this->graviteEffet) / 2;
    else if (this->vY > 2000.0f * this->graviteEffet)
        this->vY += (vY * this->graviteEffet) / 3;
    else
        this->vY += vY * this->graviteEffet;
    if (this->vY > 3000.0f)
        this->vY = 3000.0f;
    if (this->graviteEffet == 0.5f && this->vY > 500.0f)
        this->vY = 500.0f;
}


void Personnage::saut(Map *map) {
    if (this->sautOk) {
        this->sautOk = false;
        this->debutSaut = (float)SDL_GetTicks() / 1000.0f;
        if (this->isOnTuile(map, "slime", this->x, this->y) || isOverTuile(map, "slime", this->x, this->y))
            this->vY -= this->acceleration * 6.0f;
        this->vY -= this->acceleration * 3.0f;
    }
    else if (((float)SDL_GetTicks()/1000.0f)-this->debutSaut <= this->tempsSaut){
        this->vY -= this->acceleration;
    }
    else if (this->wallJumpOk && this->canWallJump(map) && this->timeOfChargeWallJump >= 0.3f) {
        this->wallJumpOk = false;
        if (this->vY > 0.0f)
            this->vY = 0.0f;
        this->vY -= this->acceleration * 10.0f;
        this->vX *= -2.0f;
        this->dirWallJump = 'N';
        if (this->vX < 0.0f)
            this->dirWallJump = 'L';
        else if (this->vX > 0.0f)
            this->dirWallJump = 'R';
        this->debutWallJump = (float)SDL_GetTicks() / 1000.0f;
    }
    else if (((float)SDL_GetTicks()/1000.0f)-this->debutWallJump <= this->tempsSaut){
        this->vY -= this->acceleration;
        if (this->dirWallJump == 'L' && this->vX > 0.0f)
            this->vX *= -1;
        else if (this->dirWallJump == 'R' && this->vX < 0.0f)
            this->vX *= -1;
    }

    int x1 = ((int)this->x) / map->getSquarreSize();
    int x2 = ((int)this->x + this->w/2) / map->getSquarreSize();
    int x3 = ((int)this->x + this->w) / map->getSquarreSize();
    int y = ((int)this->y + this->h) / map->getSquarreSize() + 1;
    if (map->test(x1, y, 'D') + map->test(x2, y, 'D') + map->test(x3, y, 'D') < 3){
        this->sautOk = true;
        this->wallJumpOk = true;
    }
}

void Personnage::move(float delta, Camera& camera, Map *map) {
    if (this->wallJumpOk && this->canWallJump(map))
        this->timeOfChargeWallJump += delta;
    else
        this->timeOfChargeWallJump = 0.0f;

    if (this->isInTuile(map, "eau", x, y))
        this->graviteEffet = 0.5f;
    else
        this->graviteEffet = 1.0f;

    if (this->mouvementPossibleX(map, delta))
        this->x += this->vX * delta;
    if(this->mouvementPossibleY(map, delta))
        this->y += this->vY * delta;
}


float Personnage::getX() {
    return this->x;
}


float Personnage::getY() {
    return this->y;
}


float Personnage::getVx() {
    return this->vX;
}


float Personnage::getVy() {
    return this->vY;
}


int Personnage::getWidth() {
    return this->w;
}


int Personnage::getHeight() {
    return this->h;
}


bool Personnage::atFin(Map *map) {
    int x = this->x / map->getSquarreSize();
    int y = this->y / map->getSquarreSize();
    return map->getEnd().inZone(x, y) || map->getEnd().inZone(x + 2, y) || map->getEnd().inZone(x, y + 3) || map->getEnd().inZone(x + 2, y + 3);
}


void Personnage::respawn() {
    this->x = this->respawnX;
    this->y = this->respawnY;
    this->vX = 0.0f;
    this->vY = 0.0f;
}


void Personnage::setRespawn(float x, float y) {
    this->respawnX = x;
    this->respawnY = y;
}

bool Personnage::isMort(Map *map) {
    float x = this->x;
    float y = this->y;

    if (this->isInTuile(map, "pique", x, y)){;
        return true;
    }

    return false;
}