//
// Created by auguste on 25/02/2022.
//

#ifndef RTB_CAMERA_H
#define RTB_CAMERA_H


class Camera {
private:
    float x, y;

public:
    Camera();
    ~Camera();

    float getX();
    float getY();
    void addPos(float x, float y);
    void setPos(float x, float y);
};


#endif //RTB_CAMERA_H
