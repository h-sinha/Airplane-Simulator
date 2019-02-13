#include "compass.h"
#include "main.h"
#include "functions.h"

Compass::Compass(float x, float y, float r) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    int n = 25;
    GLfloat vertex_buffer_data[n*9];
    GLfloat vertex_buffer_data1[n*9];
    makePolygon(0, 0, 0, r, r, n, vertex_buffer_data);
    makePolygon(0, 0, 0, r - 0.05, r - 0.05, n, vertex_buffer_data1);
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
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_RED, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data1, COLOR_GAINS_BORO, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_BLACK, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data3, COLOR_RED, GL_FILL);
}

void Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 yrotate    = glm::rotate((float) (this->rotation), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * yrotate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void Compass::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

