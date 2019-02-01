#include "functions.h"
void makeCube(float xlength, float ylength, float zlength, GLfloat vertex_buffer_data[]){
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
    for (int i = 0; i < 108; ++i)
    {
    	vertex_buffer_data[i] = vertex_buffer_data1[i];
    }
}
void makePolygon(float xoffset, float yoffset,float zoffset, float r1, float r2, int n, GLfloat vertex_buffer_data[]){
 GLfloat vertex_buffer_data1[9*n];
 int cur = 0;
 for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data1[cur] =  xoffset +  r1 * cos((2.0*PI*i)/n);
        vertex_buffer_data1[cur+1] = yoffset + r2 * sin((2.0*PI*i)/n);
        vertex_buffer_data1[cur+2] = zoffset;
        vertex_buffer_data1[cur+3] =  xoffset +  r1 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+4] = yoffset + r2 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+5] = zoffset;
        vertex_buffer_data1[cur+6] =  xoffset;
        vertex_buffer_data1[cur+7] = yoffset;
        vertex_buffer_data1[cur+8] = zoffset;
        cur += 9;
     } 
    for (int i = 0; i < cur; ++i)
    {
    	vertex_buffer_data[i] = vertex_buffer_data1[i];
    }
}
void makeCone(float xoffset, float yoffset,float zoffset, float r, float h,int n, GLfloat vertex_buffer_data[]){
 GLfloat vertex_buffer_data1[9*n];
 int cur = 0;
 for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data1[cur] =  xoffset +  r * cos((2.0*PI*i)/n);
        vertex_buffer_data1[cur+1] = yoffset + r * sin((2.0*PI*i)/n);
        vertex_buffer_data1[cur+2] = zoffset ;
        vertex_buffer_data1[cur+3] =  xoffset +  r * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+4] = yoffset + r * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+5] = zoffset ;
        vertex_buffer_data1[cur+6] =  xoffset;
        vertex_buffer_data1[cur+7] = yoffset;
        vertex_buffer_data1[cur+8] = zoffset + h;
        cur += 9;
     } 
    for (int i = 0; i < cur; ++i)
    {
    	vertex_buffer_data[i] = vertex_buffer_data1[i];
    }
}
void makePrism(float r, float h,int n, GLfloat vertex_buffer_data[]){
 GLfloat vertex_buffer_data1[9*n];
 int cur = 0;
 for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data1[cur] =  r * cos((2.0*PI*i)/n);
        vertex_buffer_data1[cur+1] = 0.0;
        vertex_buffer_data1[cur+2] = r * sin((2.0*PI*i)/n);
        vertex_buffer_data1[cur+3] =  r * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+4] =  0.0;
        vertex_buffer_data1[cur+5] =  r * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+6] = 0.0;
        vertex_buffer_data1[cur+7] = h;
        vertex_buffer_data1[cur+8] = 0.0;
        cur += 9;
     } 
    for (int i = 0; i < cur; ++i)
    {
    	vertex_buffer_data[i] = vertex_buffer_data1[i];
    }
}