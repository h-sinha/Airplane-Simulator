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
    int n = 10;
    GLfloat vertex_buffer_data[36*n];
    GLfloat g_vertex_color_data[36*n];
    int flg=0;
    // for (int i = 0; i < 9*n; i+=3)
    // {
    //     g_vertex_color_data[i] = COLOR_NEON_GREEN.r;
    //     g_vertex_color_data[i+1] = COLOR_NEON_GREEN.g;
    //     g_vertex_color_data[i+2] = COLOR_NEON_GREEN.b;
    // }
    //   for (int i = 9*n; i < 18*n; i+=3)
    // {
    //       g_vertex_color_data[i] = COLOR_BROWN.r;
    //       g_vertex_color_data[i+1] = COLOR_BROWN.g;
    //       g_vertex_color_data[i+2] = COLOR_BROWN.b;
    // }
    // for (int i = 18*n; i < 36*n; i+=18)
    // {
    //       g_vertex_color_data[i] = COLOR_BROWN.r;
    //       g_vertex_color_data[i+1] = COLOR_BROWN.g;
    //       g_vertex_color_data[i+2] = COLOR_BROWN.b;
    //       g_vertex_color_data[i+3] = COLOR_BROWN.r;
    //       g_vertex_color_data[i+4] = COLOR_BROWN.g;
    //       g_vertex_color_data[i+5] = COLOR_BROWN.b;
    //        g_vertex_color_data[i+9] = COLOR_BROWN.r;
    //       g_vertex_color_data[i+10] = COLOR_BROWN.g;
    //       g_vertex_color_data[i+11] = COLOR_BROWN.b;
    //       g_vertex_color_data[i+12] = COLOR_BROWN.r;
    //       g_vertex_color_data[i+13] = COLOR_BROWN.g;
    //       g_vertex_color_data[i+14] = COLOR_BROWN.b;
    // }
    float h = 0.5f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.5)));

    makeFrustum(2,1,h,n, vertex_buffer_data);
    this->object = create3DObject(GL_TRIANGLES, n*12, vertex_buffer_data, COLOR_BROWN, GL_FILL);
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
}

void Hills::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y,z);
}

void Hills::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

