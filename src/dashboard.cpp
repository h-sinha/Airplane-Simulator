#include "dashboard.h"
#include "main.h"
#include "functions.h"

Dashboard::Dashboard(float x, float y, float z,color_t color) {
    this->position = glm::vec3(0.0, 0.0, 0.0);
    int n = 25;
    // GLfloat vertex_buffer_data[9*n];
    const GLfloat vertex_buffer_data[]{
        -5000.0f, -5000.0f, 1000.0f,
        -5000.0f, 5000.0f, 1000.0f,
        5000.0f, -5000.0f, 1000.0f,
    };
    this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, COLOR_RED, GL_FILL);
    // this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
    // this->object2 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data2, COLOR_BLACK, GL_FILL);
}

void Dashboard::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    // draw3DObject(this->object1);
    // draw3DObject(this->object2);
}

void Dashboard::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y,z);
}

void Dashboard::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
