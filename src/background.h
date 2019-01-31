#include "main.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H


class Background {
public:
    Background() {}
    Background(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
