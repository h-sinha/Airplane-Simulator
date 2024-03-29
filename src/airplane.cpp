#include "airplane.h"
#include "main.h"
#include "functions.h"

Airplane::Airplane(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->yaw = 0;
    this->pitch = 0;
    this->roll = 0;
    this->speed = 0;
    this->xlength = 4;
    this->ylength = 1;
    this->zlength = 3;
    this->moving = 0;
    this->thex = 0;
    this->they = 0;
    this->thez = 0;
    this->y = this->p = this->r = 0;
    int n = 25;
    GLfloat vertex_buffer_data[9*n];
    GLfloat vertex_buffer_data1[9*n];
    GLfloat vertex_buffer_data2[18*n];
    GLfloat vertex_buffer_data5[9*n];
    GLfloat vertex_buffer_data6[9*n];
    GLfloat vertex_buffer_data7[9*n];
    GLfloat g_color_buffer_data[18*n];
    makePolygon(0,0,0,0.5,0.5,n,vertex_buffer_data);
    makePolygon(0,0,2.5,0.5,0.5,n,vertex_buffer_data1);
    makeCone(0,0,2.5,3,0.5,0.5,n,vertex_buffer_data5);
    makePolygon(0,0,5,0.25,0.25,n,vertex_buffer_data6);
    makePolygon(0,0,5,0.22,0.22,n,vertex_buffer_data7);

    int cur = 0;
    for (int i = 0; i < 9*n; i += 9)
    {
        for (int j = i; j < i+6; ++j)
        {
            vertex_buffer_data2[cur++] = vertex_buffer_data[j];
        }
        for (int j = i; j < i+3; ++j)
        {
            vertex_buffer_data2[cur++] = vertex_buffer_data1[j];
        }
        for (int j = cur - 9; j < cur; j += 3)
        {
            g_color_buffer_data[j] = COLOR_GAINS_BORO.r;
            g_color_buffer_data[j+1] = COLOR_GAINS_BORO.g;
            g_color_buffer_data[j+2] = COLOR_GAINS_BORO.b;
        }
        for (int j = i; j < i+6; ++j)
        {
            vertex_buffer_data2[cur++] = vertex_buffer_data1[j];
        }
         for (int j = i+3; j < i+6; ++j)
        {
            vertex_buffer_data2[cur++] = vertex_buffer_data[j];
        }
        for (int j = cur - 9; j < cur; j += 3)
        {
            g_color_buffer_data[j] = COLOR_BLACK.r;
            g_color_buffer_data[j+1] = COLOR_BLACK.g;
            g_color_buffer_data[j+2] = COLOR_BLACK.b;
        }
    }
    const GLfloat vertex_buffer_data3[]{
        -0.5f, 0.0f, 1.0f,
        -1.5f, 0.0f, 0.5f,
        -0.5f, 0.0f, 0.5f,
    };
     const GLfloat vertex_buffer_data4[]{
        0.5f, 0.0f, 1.0f,
        1.5f, 0.0f, 0.5f,
        0.5f, 0.0f, 0.5f,
    };
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->mov = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_RED, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, n*6, vertex_buffer_data2, g_color_buffer_data, GL_FILL);
    this->fan1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data3, COLOR_GAINS_BORO, GL_FILL);
    this->fan2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data4, COLOR_GAINS_BORO, GL_FILL);
    this->cockpit = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data5, COLOR_BLACK, GL_FILL);
    this->aim = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data6, COLOR_RED, GL_FILL);
    this->aim1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data7, COLOR_RED, GL_FILL);
}

void Airplane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 zrotate    = glm::rotate((float) (this->yaw), glm::vec3(0, 0, 1));
    glm::mat4 xrotate    = glm::rotate((float) (this->pitch), glm::vec3(1, 0, 0));
    glm::mat4 yrotate    = glm::rotate((float) (this->roll), glm::vec3(0, 1, 0));
    this->yaw = this->pitch = this->roll = 0.0;
    Matrices.model *= (translate *MatrixRotPlain*  yrotate * zrotate * xrotate);
    MatrixRotPlain *= zrotate * yrotate * xrotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->moving)
    draw3DObject(this->mov);
    else
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->fan1);
    draw3DObject(this->fan2);
    draw3DObject(this->cockpit);

}

void Airplane::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y,z);
}

void Airplane::tick() {
    if(this->moving == 0)
    {
        this->speed -= 0.1/60;
        this->speed = std::max(this->speed, 0.0);
    }
    else
    {
        this->speed += 0.1/60;
        this->speed = std::min(this->speed, 0.2);
    }
}

bounding_box_t Airplane::BoundingBox() {
    bounding_box_t a;
    a.xlength = this->xlength;
    a.ylength = this->ylength;
    a.zlength = this->zlength;
    a.x = this->position.x;
    a.y = this->position.y;
    a.z = this->position.z;
    return a;
}

