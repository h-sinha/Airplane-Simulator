#include "missile.h"
#include "main.h"
#include "functions.h"

Missile::Missile(float x, float y, float z, float anglex, float angley, float anglez, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->yaw = anglez;
    this->pitch = 0;
    this->roll = 0;
    this->speed = 1;
    this->xlength = 0.4;
    this->ylength = 0.4;
    this->zlength = 0.4;
    this->speed = 0.05f;
    this->thex = anglex;
    this->they = angley;
    this->time = 0;
    int n = 25;
    GLfloat vertex_buffer_data[9*n];
    makeCone(0,0,0,3,0.2,0.2,n,vertex_buffer_data);
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 zrotate    = glm::rotate((float) (this->pitch * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 xrotate    = glm::rotate((float) (this->pitch * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 yrotate    = glm::rotate((float) (this->they* M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centeBLACK at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Missile::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y,z);
}

void Missile::tick() {
    this->position.z += 0.5*cos(this->they);
    this->position.x += 0.5*sin(this->they);
    this->position.y -= 0.5*sin(this->thex);
    this->time+=(1.0f/60.f);
    this->pitch += 0.1;
}

bounding_box_t Missile::BoundingBox() {
    bounding_box_t a;
    a.xlength = this->xlength;
    a.ylength = this->ylength;
    a.zlength = this->zlength;
    a.x = this->position.x;
    a.y = this->position.y;
    a.z = this->position.z;
    return a;
}