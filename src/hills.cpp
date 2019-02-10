#include "hills.h"
#include "main.h"
#include "functions.h"

Hills::Hills(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->yaw = 0;
    this->pitch = 0;
    this->roll = 0;
    this->speed = 1;
    this->xlength = 1;
    this->ylength = 1;
    this->zlength = 2;
    int n = 20;
    GLfloat vertex_buffer_data[36*n];
    GLfloat vertex_buffer_data1[36*n];
    GLfloat vertex_buffer_data2[36*n];
    GLfloat vertex_buffer_data3[36*n];
    GLfloat vertex_buffer_data4[36*n];
    GLfloat color_buffer_data[36*n];
    float h[5], r1[5], r2[5];
    for (int i = 0; i < 5; ++i)
    {
        h[i] = 0.5f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.5)));
        r2[i] = 0.5f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.5)));
        r1[i] = r2[i] + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(3-r2[i])));
    }
    makeFrustum(0,0,0,r1[0],r2[0],h[0],n, vertex_buffer_data);
    makeFrustum(0.5,0,0.5,r1[1],r2[1],h[1],n, vertex_buffer_data1);
    makeFrustum(1,0,1,r1[2],r2[2],h[2],n, vertex_buffer_data2);
    makeFrustum(1.5,0,1.5,r1[3],r2[3],h[3],n, vertex_buffer_data3);
    makeFrustum(2,0,0.5,r1[4],r2[4],h[4],n, vertex_buffer_data4);
    for (int i = 0; i <= 36*n; i+=3)
    {
     float cl = 0.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.0)));
        color_buffer_data[i] = 0;
        color_buffer_data[i+1] = cl;
        color_buffer_data[i+2] = 0;
    }
    this->object = create3DObject(GL_TRIANGLES, n*12, vertex_buffer_data, color_buffer_data, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, n*12, vertex_buffer_data1, color_buffer_data, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, n*12, vertex_buffer_data2, color_buffer_data, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, n*12, vertex_buffer_data3, color_buffer_data, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, n*12, vertex_buffer_data4, color_buffer_data, GL_FILL);
}

void Hills::draw(glm::mat4 VP) {
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
    draw3DObject(this->object4);
}

void Hills::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y,z);
}

void Hills::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Hills::BoundingBox() {
    bounding_box_t a;
    a.xlength = this->xlength;
    a.ylength = this->ylength;
    a.zlength = this->zlength;
    a.x = this->position.x;
    a.y = this->position.y;
    a.z = this->position.z;
    return a;
}