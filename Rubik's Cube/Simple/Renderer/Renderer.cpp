#include "Renderer.h"
#include "../Maths/Maths.h"

//Utility Functions

float Renderer::map(float n,float start1,float stop1,float start2,float stop2)
{
    return ((n-start1)/(stop1-start1))*(stop2-start2)+start2;
}

float Renderer::InRange(float value,float Min,float Max)
{
    while(value > Max)
        value -= Max;
    value += Min;
    return value;
}

//Render Functions Begin

void Renderer::glbackground(float r,float g,float b)  // r,g,b values vary form 0.0f to 1.0f
{
    r = InRange(r,0,1);
    g = InRange(g,0,1);
    b = InRange(b,0,1);
    glClearColor(r,g,b,0);
}

void Renderer::background(int hexRGB)
{
    unsigned char r,g,b;

    r = (hexRGB>>16) & 0xff;                        // Extracting r,g,b values from hexadecimal
    g = (hexRGB>>8) & 0xff;
    b = hexRGB & 0xff;

    background(r,g,b);
}

void Renderer::background(float r,float g,float b)    // r,g,b values vary from 0 to 255
{
    r = map(r,0,255,0,1);                           // mapping the r,g,b values from (0-255) to (0.0,1.0)
    g = map(g,0,255,0,1);
    b = map(b,0,255,0,1);

    glbackground(r,g,b);
}

void Renderer::fill(float r,float g,float b)
{
    r = map(r,0,255,0,1);                           // mapping the r,g,b values from (0-255) to (0.0,1.0)
    g = map(g,0,255,0,1);
    b = map(b,0,255,0,1);

    glColor3f(r,g,b);
}

void Renderer::fill(int hexRGB)
{
    float r,g,b;

    r = (hexRGB>>16) & 0xff;                        // Extracting r,g,b values from hexadecimal
    g = (hexRGB>>8) & 0xff;
    b = hexRGB & 0xff;

    fill(r,g,b);
}

// 3D Render Functions

void Renderer::plane(float width,float height)
{
    float w = width/2;
    float h = height/2;

    glBegin(GL_QUADS);
        glVertex2f(-w,h);
        glVertex2f(w,h);
        glVertex2f(-w,-h);
        glVertex2f(w,-h);
    glEnd();
}

void Renderer::box(float size)
{
    box(size,size,size);
}

void Renderer::box(float size,int front,int left,int back,int right,int top,int bottom)
{
    box(size,size,size,front,left,back,right,top,bottom);
}

void Renderer::box(float length,float breadth,float height,int front,int left,int back,int right,int top,int bottom)
{
    const float l = 0.5 * length;
    const float b = 0.5 * length;
    const float h = 0.5 * length;

    glPushMatrix();
    glBegin(GL_QUADS);

        // Front Face

        fill(front);
        glVertex3f(-l, h, b);
        glVertex3f( l, h, b);
        glVertex3f( l,-h, b);
        glVertex3f(-l,-h, b);

        //Back Face

        fill(back);
        glVertex3f(-l, h,-b);
        glVertex3f( l, h,-b);
        glVertex3f( l,-h,-b);
        glVertex3f(-l,-h,-b);

        //Left Face

        fill(left);
        glVertex3f(-l,-h,-b);
        glVertex3f(-l, h,-b);
        glVertex3f(-l, h, b);
        glVertex3f(-l,-h, b);

        //Right Face

        fill(right);
        glVertex3f( l, h,-b);
        glVertex3f( l, h, b);
        glVertex3f( l,-h, b);
        glVertex3f( l,-h,-b);

        //Top Face

        fill(top);
        glVertex3f(-l, h,-b);
        glVertex3f( l, h,-b);
        glVertex3f( l, h, b);
        glVertex3f(-l, h, b);

        //Bottom Face

        fill(bottom);
        glVertex3f(-l,-h,-b);
        glVertex3f( l,-h,-b);
        glVertex3f( l,-h, b);
        glVertex3f(-l,-h, b);
    glEnd();
    glPopMatrix();
}

void Renderer::box(float length,float breadth,float height)
{
    const float l = 0.5 * length;
    const float b = 0.5 * length;
    const float h = 0.5 * length;

    glPushMatrix();
    glBegin(GL_QUADS);
        // Front Face

        glVertex3f(-l, h, b);
        glVertex3f( l, h, b);
        glVertex3f( l,-h, b);
        glVertex3f(-l,-h, b);

        //Back Face

        glVertex3f(-l, h,-b);
        glVertex3f( l, h,-b);
        glVertex3f( l,-h,-b);
        glVertex3f(-l,-h,-b);

        //Left Face

        glVertex3f(-l,-h,-b);
        glVertex3f(-l, h,-b);
        glVertex3f(-l, h, b);
        glVertex3f(-l,-h, b);

        //Right Face

        glVertex3f( l, h,-b);
        glVertex3f( l, h, b);
        glVertex3f( l,-h, b);
        glVertex3f( l,-h,-b);

        //Top Face

        glVertex3f(-l, h,-b);
        glVertex3f( l, h,-b);
        glVertex3f( l, h, b);
        glVertex3f(-l, h, b);

        //Bottom Face

        glVertex3f(-l,-h,-b);
        glVertex3f( l,-h,-b);
        glVertex3f( l,-h, b);
        glVertex3f(-l,-h, b);
    glEnd();
    glPopMatrix();
}

void Renderer::sphere(float r, int lats,int longs,GLenum mode)
{
    glPushMatrix();
    int i, j;
    for(i = 0; i <= lats; i++)
    {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(mode);
        for(j = 0; j <= longs; j++)
        {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(r * x * zr0, r * y * zr0, r * z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(r * x * zr1, r * y * zr1, r * z1);
        }
        glEnd();
    }
    glPopMatrix();
}

void Renderer::boxMesh(float size)
{
    boxMesh(size,size,size);
}

//TODO: Find a Method to Use glBegin() and glEnd() once only

void Renderer::boxMesh(float length,float breadth,float height)
{
    float l = length/2;
    float b = breadth/2;
    float h = height/2;

    glPushMatrix();

        // Front Face
    glBegin(GL_LINE_LOOP);
        glVertex3f(-l, h, b);
        glVertex3f( l, h, b);
        glVertex3f( l,-h, b);
        glVertex3f(-l,-h, b);
    glEnd();

    //Back Face
    glBegin(GL_LINE_LOOP);
        glVertex3f(-l, h,-b);
        glVertex3f( l, h,-b);
        glVertex3f( l,-h,-b);
        glVertex3f(-l,-h,-b);
    glEnd();

    //Left Face
    glBegin(GL_LINE_LOOP);
        glVertex3f(-l,-h,-b);
        glVertex3f(-l, h,-b);
        glVertex3f(-l, h, b);
        glVertex3f(-l,-h, b);
    glEnd();

    glBegin(GL_LINE_LOOP);
        //Right Face
        glVertex3f( l, h,-b);
        glVertex3f( l, h, b);
        glVertex3f( l,-h, b);
        glVertex3f( l,-h,-b);
    glEnd();

    glBegin(GL_LINE_LOOP);
        //Top Face
        glVertex3f(-l, h,-b);
        glVertex3f( l, h,-b);
        glVertex3f( l, h, b);
        glVertex3f(-l, h, b);
    glEnd();

    glBegin(GL_LINE_LOOP);
        //Bottom Face
        glVertex3f(-l,-h,-b);
        glVertex3f( l,-h,-b);
        glVertex3f( l,-h, b);
        glVertex3f(-l,-h, b);
    glEnd();

    glPopMatrix();
}
