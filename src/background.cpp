#include "background.h"
#include "main.h"

Background::Background(float x, float y,float z, color_t color) {
    this->position = glm::vec3(0.0, -10.0, 0.0);
    this->rotation = 0;
    speed = 1;
    static const GLfloat vertex_buffer_data[] = {
    	-1000.0,5.0, 1000.0,
        1000.0, 5.0, 1000.0,
        1000.0, 5.0, -1000.0,
        1000.0, 5.0, -1000.0,
        -1000.0,5.0, -1000.0,
        -1000.0,5.0, 1000.0
    };
    static const GLfloat color_buffer_data[] = {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.5f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, 1.0f,
    };
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Background::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Background::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y,z);
}

void Background::tick() {
}
