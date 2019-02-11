#include "main.h"
#ifndef FUNC_H
#define FUNC_H

void makeCube(float xlength, float ylength, float zlength, GLfloat vertex_buffer_data[]);
void makeCone(float xoffset, float yoffset,float zoffset,int dir, float r, float h,int n, GLfloat vertex_buffer_data[]);
void makePolygon(float xoffset, float yoffset,float zoffset, float r1, float r2, int n, GLfloat vertex_buffer_data[]);
void makePrism(float r, float h,int n, GLfloat vertex_buffer_data[]);
void makeFrustum(float xoffset, float yoffset, float zoffset, float r1, float r2, float h, int n, GLfloat vertex_buffer_data[]);
#endif