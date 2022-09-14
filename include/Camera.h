//
// Created by auguste on 25/02/2022.
//

#ifndef RTB_CAMERA_H
#define RTB_CAMERA_H

class Personnage;

class Camera {
private:
    float x, y, winW, winH, mapW, mapH;
    Personnage *perso;

    void avoidOutOfMap();

public:
    Camera();
    ~Camera();

    float getX();
    float getY();
    void addPosX(float x);
    void addPosY(float y);
    void setPos(float x, float y);
    void setWindowSize(float w, float h);
    void setMapSize(float w, float h);
    void linkToPerso(Personnage *perso);
};


#endif //RTB_CAMERA_H
