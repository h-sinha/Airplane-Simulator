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
void makeFrustum(float r1, float r2, float h, int n, GLfloat vertex_buffer_data[]){
	GLfloat vertex_buffer_data1[9*n], vertex_buffer_data2[9*n];
	int cur = 0;
	for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data1[cur] =   r1 * cos((2.0*PI*i)/n);
        vertex_buffer_data1[cur+1] =  0.0f;
        vertex_buffer_data1[cur+2] = r1 * sin((2.0*PI*i)/n);
        vertex_buffer_data1[cur+3] =   r1 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+4] = 0.0f;
        vertex_buffer_data1[cur+5] = r1 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+6] =  0.0f;
        vertex_buffer_data1[cur+7] = 0.0f;
        vertex_buffer_data1[cur+8] = 0.0f;
        cur += 9;
     } 
     cur = 0;
     for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data2[cur] =   h + r2 * cos((2.0*PI*i)/n);
        vertex_buffer_data2[cur+1] =  h+0.0f;
        vertex_buffer_data2[cur+2] = h + r2 * sin((2.0*PI*i)/n);
        vertex_buffer_data2[cur+3] =  h+ r2 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data2[cur+4] = h+0.0f;
        vertex_buffer_data2[cur+5] = h + r2 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data2[cur+6] = h + 0.0f;
        vertex_buffer_data2[cur+7] = h;
        vertex_buffer_data2[cur+8] = h + 0.0f;
        cur += 9;
     } 
 	for (int i = 0; i < 9*n; ++i)
 		vertex_buffer_data[i] = vertex_buffer_data1[i];
 	for (int i = 0; i < 9*n; ++i)
 		vertex_buffer_data[i+9*n] = vertex_buffer_data2[i];
 	cur = 18*n;
    for (int i = 0; i < 9*n; i += 9)
    {
        for (int j = i; j < i+3; ++j)
        {
            vertex_buffer_data[cur++] = vertex_buffer_data1[j];
        }
        for (int j = i+6; j < i+9; ++j)
        {
            vertex_buffer_data[cur++] = vertex_buffer_data1[j];
        }
        for (int j = i+3; j < i+6; ++j)
        {
            vertex_buffer_data[cur++] = vertex_buffer_data2[j];
        }
        for (int j = i; j < i+3; ++j)
        {
            vertex_buffer_data[cur++] = vertex_buffer_data2[j];
        }
         for (int j = i+6; j < i+9; ++j)
        {
            vertex_buffer_data[cur++] = vertex_buffer_data2[j];
        }
         for (int j = i+3; j < i+6; ++j)
        {
            vertex_buffer_data[cur++] = vertex_buffer_data1[j];
        }
    }
}