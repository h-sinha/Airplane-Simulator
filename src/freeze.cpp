#include "freeze.h"
#include "main.h"
#include "functions.h"

Freeze::Freeze(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->yaw = 0;
    this->pitch = 0;
    this->roll = 0;
    this->speed = 1;
    this->xlength = 0.5;
    this->ylength = 0.5;
    this->zlength = 0.2;
    int n = 10;
    GLfloat vertex_buffer_data[36*n];
    GLfloat vertex_buffer_data1[36*n];
    // makeFrustum(0,0,0,0.2, 0.2, 0.2, n, vertex_buffer_data);
    // makeFrustum(0,0,0,0.1, 0.1, 0.2, n, vertex_buffer_data1);
    makePolygon(0,0,0,0.5,0.5,n,vertex_buffer_data);
    makePolygon(0,0,0.2,0.5,0.5,n,vertex_buffer_data1);
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    // this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    GLfloat vertex_buffer_data2[]{
      -0.05f, 0.0f, 0.0f,
      0.05f, 0.0f, 0.0f,
      0.0f, 0.25f, 0.0f,
    };
    GLfloat vertex_buffer_data3[]{
     -0.05f, 0.0f, 0.0f,
      0.05f, 0.0f, 0.0f,
      0.0f, -0.25f, 0.0f,
    };
    this->object1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_GAINS_BORO, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data3, COLOR_GAINS_BORO, GL_FILL);
}

void Freeze::draw(glm::mat4 VP) {
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
}

void Freeze::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y,z);
}

void Freeze::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Freeze::BoundingBox() {
    bounding_box_t a;
    a.xlength = this->xlength;
    a.ylength = this->ylength;
    a.zlength = this->zlength;
    a.x = this->position.x;
    a.y = this->position.y;
    a.z = this->position.z;
    return a;
}