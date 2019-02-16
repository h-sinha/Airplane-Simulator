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
    // if(bomb == 2)this->speed = 0.4;
    this->xlength = 0.2;
    this->ylength = 0.2;
    this->zlength = 0.2;
    this->thex = anglex;
    this->they = angley;
    this->thez = anglez;
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
    // No need as coords centeBLACK at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
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
        this->position.z += this->speed*cos(this->they);
        this->position.x += this->speed*sin(this->they);
        this->position.y -= this->speed*sin(this->thex);
        this->time+=(1.0f/60.f);
        return;
    }
    if(this->bomb != 1)
    {
        this->position.z += this->speed*thez;
        this->position.x += this->speed*thex;
    }
    this->position.y -= this->speed*they;
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