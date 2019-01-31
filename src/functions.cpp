#include "functions.h"
void fillarray(float xlength, float ylength, float zlength, GLfloat vertex_buffer_data[]){
 GLfloat vertex_buffer_data1[] = {
         -xlength/2.0f ,-ylength/2.0f ,-zlength/2.0f, // triangle 1 : begin
        -xlength/2.0f ,-ylength/2.0f , zlength/2.0f,
        -xlength/2.0f , ylength/2.0f , zlength/2.0f, // triangle 1 : end
        xlength/2.0f , ylength/2.0f ,-zlength/2.0f, // triangle 2 : begin
        -xlength/2.0f ,-ylength/2.0f ,-zlength/2.0f,
        -xlength/2.0f , ylength/2.0f ,-zlength/2.0f, // triangle 2 : end
        xlength/2.0f ,-ylength/2.0f , zlength/2.0f,
        -xlength/2.0f ,-ylength/2.0f ,-zlength/2.0f,
        xlength/2.0f ,-ylength/2.0f ,-zlength/2.0f,
        xlength/2.0f , ylength/2.0f ,-zlength/2.0f,
        xlength/2.0f ,-ylength/2.0f ,-zlength/2.0f,
        -xlength/2.0f ,-ylength/2.0f ,-zlength/2.0f,
        -xlength/2.0f ,-ylength/2.0f ,-zlength/2.0f,
        -xlength/2.0f , ylength/2.0f , zlength/2.0f,
        -xlength/2.0f , ylength/2.0f ,-zlength/2.0f,
        xlength/2.0f ,-ylength/2.0f , zlength/2.0f,
        -xlength/2.0f ,-ylength/2.0f , zlength/2.0f,
        -xlength/2.0f ,-ylength/2.0f ,-zlength/2.0f,
        -xlength/2.0f , ylength/2.0f , zlength/2.0f,
        -xlength/2.0f ,-ylength/2.0f , zlength/2.0f,
        xlength/2.0f ,-ylength/2.0f , zlength/2.0f,
        xlength/2.0f , ylength/2.0f , zlength/2.0f,
        xlength/2.0f ,-ylength/2.0f ,-zlength/2.0f,
        xlength/2.0f , ylength/2.0f ,-zlength/2.0f,
        xlength/2.0f ,-ylength/2.0f ,-zlength/2.0f,
        xlength/2.0f , ylength/2.0f , zlength/2.0f,
        xlength/2.0f ,-ylength/2.0f , zlength/2.0f,
        xlength/2.0f , ylength/2.0f , zlength/2.0f,
        xlength/2.0f , ylength/2.0f ,-zlength/2.0f,
        -xlength/2.0f , ylength/2.0f ,-zlength/2.0f,
        xlength/2.0f , ylength/2.0f , zlength/2.0f,
        -xlength/2.0f , ylength/2.0f ,-zlength/2.0f,
        -xlength/2.0f , ylength/2.0f , zlength/2.0f,
        xlength/2.0f , ylength/2.0f , zlength/2.0f,
        -xlength/2.0f , ylength/2.0f , zlength/2.0f,
        xlength/2.0f ,-ylength/2.0f , zlength/2.0f
       
    };
    for (int i = 0; i < 105; ++i)
    {
    	vertex_buffer_data[i] = vertex_buffer_data1[i];
    }
}