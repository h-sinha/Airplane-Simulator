#include "main.h"

#ifndef AIRPLANE_H
#define AIRPLANE_H


class Airplane {
public:
    Airplane() {}
    Airplane(float x, float y,float z, color_t color);
    glm::vec3 position;
    int moving;
    float yaw, pitch, roll;
    void draw(glm::mat4 VP);
    bounding_box_t BoundingBox();
    void set_position(float x, float y, float z);
    void tick();
    double speed, thex, they, thez;
    double xlength, ylength, zlength;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *fan1;
    VAO *fan2;
    VAO *cockpit;
    VAO *mov;
};

#endif // BALL_H
