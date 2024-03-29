#include "missile.h"
#include "main.h"
#include "functions.h"

Missile::Missile(int bomb,float x, float y, float z, float anglex, float angley, float anglez, color_t color) {
    this->position = glm::vec3(x, y, z + 0.1);
    this->yaw = anglez;
    this->pitch = 0;
    this->bomb = bomb;
    this->roll = 0;
    this->speed = 1;
    if(bomb == 2)this->speed = 0.4;
    this->xlength = 0.2;
    this->ylength = 0.2;
    this->zlength = 0.2;
    this->thex = anglex;
    this->they = angley;
    this->thez = anglez;
    if(this->bomb == 0)
    {
        this->thex = MatrixRotPlain[2][0];
        this->they = MatrixRotPlain[2][1];
        this->thez = MatrixRotPlain[2][2];
    }
    this->time = 0;
    int n = 25;
    GLfloat vertex_buffer_data[36*n];
    makeFrustum(0,0,0,0.1,0.1,0.2,n,vertex_buffer_data);

    this->object = create3DObject(GL_TRIANGLES, n*12, vertex_buffer_data, color, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 zrotate    = glm::rotate((float) (this->pitch * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 xrotate    = glm::rotate((float) (this->pitch * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 yrotate    = glm::rotate((float) (this->they* M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Missile::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y,z);
}

void Missile::tick() {
    if(this->bomb == 2){
        this->position.z += this->speed*this->thez;
        this->position.x += this->speed*this->thex;
        this->position.y += this->speed*this->they;
        this->time+=(1.0f/60.f);
        return;
    }
    if(this->bomb == 0)
    {
        this->position.z += this->thez;
        this->position.y += this->they;
        this->position.x += this->thex;
        this->time+=(1.0f/60.f);
        return;
    }
    this->position.y -= this->speed;
    this->time+=(1.0f/60.f);
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