#include "speedometer.h"
#include "main.h"
#include "functions.h"

Speed::Speed(float x, float y, float r) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    int n = 25;
    GLfloat vertex_buffer_data[n*9];
    GLfloat vertex_buffer_data1[n*9];
    makePolygon(0, 0, 0, r, r, n, vertex_buffer_data);
    makePolygon(0, 0, 0, r - 0.02, r - 0.02, n, vertex_buffer_data1);
    GLfloat vertex_buffer_data3[]{
     -0.025f, 0.0f, 0.0f,
      0.025f, 0.0f, 0.0f,
      0.0f, 0.125f, 0.0f,
    };
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_NEON_GREEN, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data3, COLOR_NEON_GREEN, GL_FILL);
}

void Speed::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 yrotate    = glm::rotate((float) (this->rotation), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * yrotate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object3);
}

void Speed::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

