#include "volcano.h"
#include "main.h"
#include "functions.h"

Volcano::Volcano(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->yaw = 0;
    this->pitch = 0;
    this->roll = 0;
    this->speed = 1;
    this->xlength = 1.2;
    this->ylength = 100;
    this->zlength = 1.2;
    int n = 10;
    GLfloat vertex_buffer_data[36*n];
    GLfloat vertex_buffer_data1[36*n];
    GLfloat color_buffer_data[36*n];
    makeFrustum(0,0,0,0.8,0.1,1.0,n, vertex_buffer_data);
    makeFrustum(0,0,0,0.4,0.2,0.8,n, color_buffer_data);
    makeFrustum(0,1.0,0,0.02,0.02,1000,n, vertex_buffer_data1);
    this->object = create3DObject(GL_TRIANGLES, n*12, vertex_buffer_data, color_buffer_data, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, n*12, vertex_buffer_data1,COLOR_RED, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 zrotate    = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 xrotate    = glm::rotate((float) (this->pitch * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 yrotate    = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * zrotate * xrotate * yrotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Volcano::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y,z);
}

void Volcano::tick() {
}

bounding_box_t Volcano::BoundingBox() {
    bounding_box_t a;
    a.xlength = this->xlength;
    a.ylength = this->ylength;
    a.zlength = this->zlength;
    a.x = this->position.x;
    a.y = this->position.y;
    a.z = this->position.z;
    return a;
}