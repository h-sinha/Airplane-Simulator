#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(float x, float y,float z, color_t color);
    glm::vec3 position;
    float yaw, pitch, roll;
    bounding_box_t BoundingBox();
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    double xlength, ylength, zlength;
private:
    VAO *object;
};

#endif // BALL_H
