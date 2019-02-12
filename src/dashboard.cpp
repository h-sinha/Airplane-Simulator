#include "dashboard.h"
#include "main.h"

Dashboard::Dashboard(float x, float y, float xx, float yy) {
    this->position = glm::vec3(x, y, 0);
    GLfloat vertex_buffer_data[] = {
       0.0f, 0.0f, 0.0f,
       xx, 0.0f, 0.0f,
       0.0f, yy, 0.0f,
       xx, yy, 0.0f,
       0.0f, yy, 0.0f,
       xx, 0.0f, 0.0f,
     };
    this->line = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Dashboard::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->line);
}

void Dashboard::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

