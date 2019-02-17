#include "checkpoint.h"
#include "main.h"
#include "functions.h"

Checkpoint::Shooter(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->yaw = 0;
    this->pitch = 0;
    this->roll = 0;
    this->speed = 1;
    this->xlength = 1;
    this->ylength = 1;
    this->zlength = 2;
    this->active = 0;
    int n = 20;
    GLfloat vertex_buffer_data[36*n];
    GLfloat vertex_buffer_data1[36*n];
    GLfloat vertex_buffer_data2[36*n];
    makeFrustum(0,0,0,0.5f,0.5f,0.5f,n, vertex_buffer_data);
    makeFrustum(0,0.5,0,0.25f,0.25f,0.25f,n, vertex_buffer_data1);
    // makeFrustum(0,0.75,0,0.125f,0.125f,0.125f,n, vertex_buffer_data2);
    makeCone(0,0.72,0,2,0.05,0.5,n,vertex_buffer_data2);
    GLfloat vertex_buffer_data3[]{
        0.0f, 0.92f, 0.0f,
        0.5f, 0.92f, 0.0f,
        0.0f, 1.12f, 0.0f,
    };
    this->object = create3DObject(GL_TRIANGLES, n*12, vertex_buffer_data, COLOR_BROWN, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, n*12, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data2, COLOR_BLACK, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data3, COLOR_RED, GL_FILL);
}

void Shooter::draw(glm::mat4 VP) {
    // if(this->active == 0)return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 zrotate    = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 xrotate    = glm::rotate((float) (this->pitch * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 yrotate    = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centeBROWN at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * zrotate * xrotate * yrotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void Checkpoint::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y,z);
}

void Checkpoint::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Checkpoint::BoundingBox() {
    bounding_box_t a;
    a.xlength = this->xlength;
    a.ylength = this->ylength;
    a.zlength = this->zlength;
    a.x = this->position.x;
    a.y = this->position.y;
    a.z = this->position.z;
    return a;
}