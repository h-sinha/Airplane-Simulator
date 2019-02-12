#include "main.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H


class Dashboard {
public:
    Dashboard() {}
    Dashboard(float x, float y, float xx, float yy);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    double speed;
private:
    VAO *line;
};

#endif // PLAYER_H
