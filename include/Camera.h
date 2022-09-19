//
// Created by auguste on 25/02/2022.
//

#ifndef RTB_CAMERA_H
#define RTB_CAMERA_H

#include "../include/Background.h"

class Camera {
private:
    float x, y, winW, winH, mapW, mapH, mapSize;

public:
    Camera();
    ~Camera();

    float getX();
    float getY();
    void tick(float x, float y, float vX, float vY, int w, int h, Background *background, float delta);
    void setWindowSize(float w, float h);
    void setMapSize(float w, float h, float mapSize);
};


#endif //RTB_CAMERA_H
