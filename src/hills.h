#include "main.h"

#ifndef HILLS_H
#define HILLS_H


class Hills {
public:
    Hills() {}
    Hills(float x, float y,float z);
    glm::vec3 position;
    float yaw, pitch, roll;
    void draw(glm::mat4 VP);
    bounding_box_t BoundingBox();
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    double xlength, ylength, zlength;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // BALL_H
