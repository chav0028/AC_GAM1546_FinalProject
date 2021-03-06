#ifndef __OGL_Shaders_H__
#define __OGL_Shaders_H__

void myassert(bool condition);

void OutputMessage(const char* message, ...);

void CheckForGLErrors();

char* LoadCompleteFile(const char* filename);

double MyGetSystemTime();

GLuint LoadTexture(const char* filename);
void Flip32BitImageVertically(unsigned char* buffer, unsigned int width, unsigned int height);

void GetMouseCoordinates(int* mx, int* my);

class MyColor
{
public:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    MyColor()
    {
    }
    MyColor(unsigned char nr, unsigned char ng, unsigned char nb, unsigned char na)
    {
        r = nr;
        g = ng;
        b = nb;
        a = na;
    }
};

#endif //__OGL_Shaders_H__
