#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
   	Compass(float x, float y, float r);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    double rotation;
    void set_position(float x, float y);
    double speed;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // PLAYER_H
