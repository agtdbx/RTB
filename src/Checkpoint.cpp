//
// Created by auguste on 25/04/22.
//

#include "../include/Checkpoint.h"

// Méthodes privées




// Méthodes publiques

Checkpoint::Checkpoint(int x, int y, int id) {
    this->x = x;
    this->y = y;
    this->id = id;
}

Checkpoint::~Checkpoint() {

}

int Checkpoint::getX() {
    return this->x;
}

int Checkpoint::getY() {
    return this->y;
}

int Checkpoint::getId() {
    return this->id;
}