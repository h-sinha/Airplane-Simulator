#include "parachute.h"
#include "main.h"
#include "functions.h"

Parachute::Parachute(float x, float y, float z) {
    this->yaw = 0;
    this->pitch = 0;
    this->roll = 0;
    this->speed = 0.1;
    this->xlength = 2.5;
    this->ylength = 2.5;
    this->zlength = 2.5;
    int n = 20;
    GLfloat vertex_buffer_data[36*n];
    GLfloat vertex_buffer_data1[36*n];
    GLfloat vertex_buffer_data2[36*n];
    GLfloat color_buffer_data2[36*n];
    GLfloat color_buffer_data[36*n];
    makeCube(1.25,1.25,1.25,vertex_buffer_data);
    makeCone(0.0,1.25,0.0,2, 1.25, 1.25, n,vertex_buffer_data2);
    int cur = 0;
     for (int i = 0; i < n; ++i)
     {
        if(i%2==0)
        {
            for (int j = 9*i; j < 9*i + 9 ; j += 3)
            {
                color_buffer_data[j] = COLOR_RED.r;
                color_buffer_data[j+1] = COLOR_RED.g;
                color_buffer_data[j+2] = COLOR_RED.b;
            }
        }
        else
        {
             for (int j = 9*i; j < 9*i + 9 ; j += 3)
            {
                color_buffer_data[j] = COLOR_GREEN.r;
                color_buffer_data[j+1] = COLOR_GREEN.g;
                color_buffer_data[j+2] = COLOR_GREEN.b;
            }
        }
     } 
    float r = 1.25;
     for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data1[cur] =  r * cos((2.0*PI*i)/n);
        vertex_buffer_data1[cur+1] = 1.25;
        vertex_buffer_data1[cur+2] = r * sin((2.0*PI*i)/n);
        vertex_buffer_data1[cur+3] =  0.0;
        vertex_buffer_data1[cur+4] = 0.6;
        vertex_buffer_data1[cur+5] = 0.0;
        cur += 6;
     } 

    float posx,posy, posz;
    posx = -50.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100.0)));
    posz = -50.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100.0)));
    posy = 30.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(20.0)));
    this->position = glm::vec3(posx, posy, posz);
    this->object = create3DObject(GL_TRIANGLES, 3*12, vertex_buffer_data, COLOR_RED, GL_FILL);
    this->object1 = create3DObject(GL_LINES, 2*n, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data2, color_buffer_data, GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {
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

void Parachute::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y,z);
}

void Parachute::tick() {
    this->roll += 1;
    // this->position.x -= speed;
    this->position.y -= this->speed;
    if(this->position.y < 0.0)
    {
        float posx,posy, posz;
        posx = -50.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100.0)));
        posz = -50.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100.0)));
        posy  = 30.0f;
        this->set_position(posx, posy, posz);
    }
}

bounding_box_t Parachute::BoundingBox() {
    bounding_box_t a;
    a.xlength = this->xlength;
    a.ylength = this->ylength;
    a.zlength = this->zlength;
    a.x = this->position.x;
    a.y = this->position.y;
    a.z = this->position.z;
    return a;
}