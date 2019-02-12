#include "functions.h"
void makeCube(float xlength, float ylength, float zlength, GLfloat vertex_buffer_data[]){
 GLfloat vertex_buffer_data1[] = {
         -xlength/2.0f ,-ylength/2.0f ,-zlength/2.0f, // trideg 1 : begin
        -xlength/2.0f ,-ylength/2.0f , zlength/2.0f,
        -xlength/2.0f , ylength/2.0f , zlength/2.0f, // trideg 1 : end
        xlength/2.0f , ylength/2.0f ,-zlength/2.0f, // trideg 2 : begin
        -xlength/2.0f ,-ylength/2.0f ,-zlength/2.0f,
        -xlength/2.0f , ylength/2.0f ,-zlength/2.0f, // trideg 2 : end
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
void makeCone(float xoffset, float yoffset,float zoffset,int dir, float r, float h,int n, GLfloat vertex_buffer_data[]){
 GLfloat vertex_buffer_data1[9*n];
 int cur = 0;
 if(dir == 3){
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
 }
 else if(dir == 2){
    for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data1[cur] =  xoffset +  r * cos((2.0*PI*i)/n);
        vertex_buffer_data1[cur+1] = yoffset;
        vertex_buffer_data1[cur+2] = zoffset + r * sin((2.0*PI*i)/n) ;
        vertex_buffer_data1[cur+3] =  xoffset +  r * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+4] = yoffset;
        vertex_buffer_data1[cur+5] = zoffset + r * sin((2.0*PI*(i+1))/n) ;
        vertex_buffer_data1[cur+6] =  xoffset;
        vertex_buffer_data1[cur+7] = yoffset + h;
        vertex_buffer_data1[cur+8] = zoffset;
        cur += 9;
     } 
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
void makeFrustum(float xoffset, float yoffset, float zoffset, float r1, float r2, float h, int n, GLfloat vertex_buffer_data[]){
	GLfloat vertex_buffer_data1[9*n], vertex_buffer_data2[9*n];
	int cur = 0;
	for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data1[cur] =  xoffset + r1 * cos((2.0*PI*i)/n);
        vertex_buffer_data1[cur+1] =   yoffset + 0.0f;
        vertex_buffer_data1[cur+2] =   zoffset + r1 * sin((2.0*PI*i)/n);
        vertex_buffer_data1[cur+3] =  xoffset +   r1 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+4] =   yoffset + 0.0f;
        vertex_buffer_data1[cur+5] =  zoffset + r1 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+6] =  xoffset +   0.0f;
        vertex_buffer_data1[cur+7] =   yoffset + 0.0f;
        vertex_buffer_data1[cur+8] =  zoffset + 0.0f;
        cur += 9;
     } 
     cur = 0;
     for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data2[cur] =   xoffset +  r2 * cos((2.0*PI*i)/n);
        vertex_buffer_data2[cur+1] =   yoffset +  h+0.0f;
        vertex_buffer_data2[cur+2] =  zoffset  + r2 * sin((2.0*PI*i)/n);
        vertex_buffer_data2[cur+3] =  xoffset + r2 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data2[cur+4] =   yoffset + h+0.0f;
        vertex_buffer_data2[cur+5] =  zoffset + r2 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data2[cur+6] = xoffset +  0.0f;
        vertex_buffer_data2[cur+7] =  yoffset +  h;
        vertex_buffer_data2[cur+8] =  zoffset  + 0.0f;
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
std::string sevenSegment(char s)
{
    switch(s)
    {
        case '1':
            return "0011000";
        case '2':
            return "0110111";
        case '3':
            return "0111101";
        case '4':
            return "1011001";
        case '5':
            return "1101101";
        case '6':
            return "1101111";
        case '7':
            return "0111000";
        case '8':
            return "1111111";
        case '9':
            return "1111101";
        case '0':
            return "1111110";
        case 'S':
            return "1101101";
        case 'C':
            return "1100110";
        case 'O':
            return "1111110";
        case 'R':
            return "1100010";
        case 'E':
            return "1100111";
        case 'A':
            return "1111011";
        case 'L':
            return "1000110";
        case 'F':
            return "1100011";
        case '-':
            return "0000001";
        default:
            return "0000000";
    }
}