#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(int bomb,float x, float y,float z,float anglex, float angley,float anglez, color_t color);
    glm::vec3 position;
    float yaw, pitch, roll;
    int bomb;
    bounding_box_t BoundingBox();
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed, thex, they, time;
    double xlength, ylength, zlength;
private:
    VAO *object;
};

#endif // BALL_H
