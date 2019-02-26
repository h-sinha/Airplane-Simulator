#include "arrow.h"
#include "main.h"
#include "functions.h"

Arrow::Arrow(float x, float y, float z) {
    this->position = glm::vec3(x, y  , z);
    this->yaw = 0;
    this->pitch = 0;
    this->roll = 0;
    this->speed = 1;
    this->xlength = 1;
    this->ylength = 1;
    this->zlength = 2;
    this->active = 0;
    GLfloat vertex_buffer_data1[108];
    GLfloat vertex_buffer_data[]{
          0.0f, 0.2f, 0.4f,
        -0.2f, 0.2f, 0.0f,
        0.2f, 0.2f, 0.0f,

        0.0f, 0.0f, 0.4f,
        -0.2f, 0.0f, 0.0f,
        0.2f, 0.0f, 0.0f,

        0.0f, 0.0f, 0.4f,
        0.0f, 0.2f, 0.4f,
        -0.2f, 0.2f, 0.0f,

        0.0f, 0.0f, 0.4f,
        -0.2f, 0.0f, 0.0f,
        -0.2f, 0.2f, 0.0f,

         0.0f, 0.0f, 0.4f,
        0.0f, 0.2f, 0.4f,
        0.2f, 0.2f, 0.0f,

        0.0f, 0.0f, 0.4f,
        0.2f, 0.0f, 0.0f,
        0.2f, 0.2f, 0.0f,

    };
    makeCube(0,0.1,0,0.12,0.1, 0.6, vertex_buffer_data1);
    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, COLOR_RED, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 3*12, vertex_buffer_data1, COLOR_RED, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 zrotate    = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 xrotate    = glm::rotate((float) ( M_PI / 2.0f), glm::vec3(1, 0, 0));
    glm::mat4 yrotate    = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 scl    = glm::scale(glm::vec3(4.0f, 4.0f, 4.0f));
    Matrices.model *= (translate * zrotate * xrotate * yrotate *scl);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Arrow::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y,z);
}

void Arrow::tick() {
}

bounding_box_t Arrow::BoundingBox() {
    bounding_box_t a;
    a.xlength = this->xlength;
    a.ylength = this->ylength;
    a.zlength = this->zlength;
    a.x = this->position.x;
    a.y = this->position.y;
    a.z = this->position.z;
    return a;
}