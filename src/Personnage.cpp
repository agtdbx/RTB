//
// Created by auguste on 22/02/2022.
//

#include "../include/Personnage.h"
#include <SDL.h>


// Private methodes
bool Personnage::isInTuile(Map map, std::string nomTuile, float x, float y) {
    int x1 = (int)(x)/20;
    int x2 = (int)(x + this->w/2)/20;
    int x3 = (int)(x + this->w)/20;
    int y1 = (int)(y)/20;
    int y2 = (int)(y + this->h/3)/20;
    int y3 = (int)(y + (this->h/3)*2)/20;
    int y4 = (int)(y + this->h)/20;

    if (map.get(x1, y1).getType() == nomTuile || map.get(x2, y1).getType() == nomTuile || map.get(x3, y1).getType() == nomTuile ||
        map.get(x1, y2).getType() == nomTuile || map.get(x2, y2).getType() == nomTuile || map.get(x3, y2).getType() == nomTuile ||
        map.get(x1, y3).getType() == nomTuile || map.get(x2, y3).getType() == nomTuile || map.get(x3, y3).getType() == nomTuile ||
        map.get(x1, y4).getType() == nomTuile || map.get(x2, y4).getType() == nomTuile || map.get(x3, y4).getType() == nomTuile)
            return true;
    return false;
}

bool Personnage::mouvementPossibleX(Map map, float delta) {
    int x = (int)(this->x + this->vX*delta);
    int y = (int)(this->y);

    if (this->isInTuile(map, "mur", x, y) || this->isInTuile(map, "glace", x, y))
    {
        this->vX = 0.0f;
        return false;
    }
    if (this->isInTuile(map, "slime", x, y))
        this->vX *= -1.0f;
    return true;
}


bool Personnage::mouvementPossibleY(Map map, float delta) {
    int x = (int)(this->x);
    int y = (int)(this->y + this->vY*delta);

    if (this->isInTuile(map, "mur", x, y) || this->isInTuile(map, "glace", x, y)
        || (this->isInTuile(map, "plateforme", x, y) && this->vY > 0.0f))
    {
        this->vY = 0.0f;
        return false;
    }
    if (this->isInTuile(map, "slime", x, y))
        this->vY *= -1.0f;
    return true;
}


// Public methodes
Personnage::Personnage() {
    this->x = 50.0f;
    this->y = 50.0f;
    this->w = 40;
    this->h = 59;
    this->vX = 0.0f;
    this->vY = 0.0f;
    this->respawnX = 50.0f;
    this->respawnY = 50.0f;
}


Personnage::Personnage(float x, float y) {
    this->respawnX = x;
    this->respawnY = y;
    this->x = x;
    this->y = y;
    this->w = 39;
    this->h = 59;
    this->vX = 0.0f;
    this->vY = 0.0f;
    this->vitesse = 500.0f;
    this->acceleration = 50.0f;
    this->debutSaut = 0.0f;
    this->tempsSaut = 0.2f;
    this->sautOk = false;
    this->graviteEffet = 1.0f;
}


Personnage::~Personnage() {

}


void Personnage::draw(SDL_Renderer *renderer, Camera camera) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
    int x = this->x - camera.getX();
    int y = this->y - camera.getY();
    SDL_Rect rect = {x, y, this->w, this->h};
    SDL_RenderFillRect(renderer, &rect);
}


void Personnage::deplacementX(char direction, Map map) {
    if (direction == 'g') {
        this->vX = -this->vitesse;
    } else if (direction == 'd') {
        this->vX = this->vitesse;
    } else {
        int x1 = ((int)this->x)/20;
        int x2 = ((int)this->x + this->w/2)/20;
        int x3 = ((int)this->x + this->w)/20;
        int y = ((int)this->y + this->h)/20;
        if (map.touch(x1, y+1) == 3 || map.touch(x2, y+1) == 3 || map.touch(x3, y+1) == 3){
            if (this->vX >= 10.0f) {
                this->vX -= 10.0f;
            } else if (this->vX <= -10.0f) {
                this->vX += 10.0f;
            }
            else{
                this->vX = 0.0f;
            }
        }
        else{
            this->vX = 0.0f;
        }

    }
    if (this->vX > this->vitesse) {
        this->vX = this->vitesse;
    }
    else if (this->vX < -this->vitesse){
        this->vX = -this->vitesse;
    }
}


void Personnage::addVx(float vX) {
    this->vX += vX;
    if (this->vX > 1000.0f){
        this->vX = 1000.0f;
    }
}


void Personnage::stopVx() {
    this->vX = 0.0f;
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
    this->vY += vY * this->graviteEffet;
    if (this->vY > 1000.0f * this->graviteEffet){
        this->vY = 1000.0f * this->graviteEffet;
    }
}


void Personnage::stopVy() {
    this->vY = 0.0f;
}

void Personnage::saut(float vY, Map map) {
    if (this->sautOk){
        this->sautOk = false;
        this->debutSaut = (float)SDL_GetTicks()/1000.0f;
        this->vY -= vY*3;
    }
    else if (((float)SDL_GetTicks()/1000.0f)-this->debutSaut <= this->tempsSaut){
        this->vY -= vY;
    }

    int x1 = ((int)this->x)/20;
    int x2 = ((int)this->x + this->w/2)/20;
    int x3 = ((int)this->x + this->w)/20;
    int y = ((int)this->y + this->h)/20 + 1;
    if (!map.test(x1, y, 'D') || !map.test(x2, y, 'D') || !map.test(x3, y, 'D')){
        this->sautOk = true;
    }
}

void Personnage::move(float delta, Camera& camera, Map map) {
    if (this->isInTuile(map, "eau", x, y))
        this->graviteEffet = 0.5f;
    else
        this->graviteEffet = 1.0f;
    if (this->mouvementPossibleX(map, delta)){
        this->x += this->vX * delta;
        camera.addPosX(this->vX * delta);
    }
    if(this->mouvementPossibleY(map, delta)){
        this->y += this->vY * delta;
        camera.addPosY(this->vY * delta);
    }
}


float Personnage::getAcceleration() {
    return this->acceleration;
}


float Personnage::getX() {
    return this->x;
}


float Personnage::getY() {
    return this->y;
}


int Personnage::getWidth() {
    return this->w;
}


int Personnage::getHeight() {
    return this->h;
}


bool Personnage::atFin(Map map) {
    return this->x + this->w >= map.getEnd().getX()*20 && this->x <= map.getEnd().getX()*20 + 3*20 && this->y + this->h >= map.getEnd().getY()*20 && this->y <= map.getEnd().getY()*20 + 3*20;
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

bool Personnage::isMort(Map map) {
    int x1 = (int)(this->x)/20;
    int x2 = (int)(this->x + this->w/2)/20;
    int x3 = (int)(this->x + this->w)/20;
    int y1 = (int)(this->y)/20;
    int y2 = (int)(this->y + this->h/3)/20;
    int y3 = (int)(this->y + (this->h/3)*2)/20;
    int y4 = (int)(this->y + this->h)/20;

    if (map.touch(x1, y1) == 4 || map.touch(x1, y2) == 4 || map.touch(x1, y3) == 4 || map.touch(x1, y4) == 4 ||
        map.touch(x2, y1) == 4 || map.touch(x2, y2) == 4 || map.touch(x2, y3) == 4 || map.touch(x2, y4) == 4 ||
        map.touch(x3, y1) == 4 || map.touch(x3, y2) == 4 || map.touch(x3, y3) == 4 || map.touch(x3, y4) == 4){;
        return true;
    }

    return false;
}