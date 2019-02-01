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
    int n = 5;
    GLfloat vertex_buffer_data[9*n];
    GLfloat g_vertex_color_data[9*n];
    int flg=0;
    for (int i = 0; i < 9*n; i+=3)
    {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        g_vertex_color_data[i] = r;
        g_vertex_color_data[i+1] = g;
        g_vertex_color_data[i+2] = b;
        // if(i%9 == 6 || i%9 == 7 ||i%9 == 8)
        // {
        //         g_vertex_color_data[i] = COLOR_BLUE.r;
        //         g_vertex_color_data[i+1] = COLOR_BLUE.g;
        //         g_vertex_color_data[i+2] = COLOR_BLUE.b;
        // }
        // else
        // {
        //         g_vertex_color_data[i] = COLOR_GREEN.r;
        //         g_vertex_color_data[i+1] = COLOR_GREEN.g;
        //         g_vertex_color_data[i+2] = COLOR_GREEN.b;
        // }
    }
    makePrism(0.5,1,n, vertex_buffer_data);
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, g_vertex_color_data, GL_FILL);
}

void Hills::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 zrotate    = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 xrotate    = glm::rotate((float) (this->pitch * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 yrotate    = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
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

