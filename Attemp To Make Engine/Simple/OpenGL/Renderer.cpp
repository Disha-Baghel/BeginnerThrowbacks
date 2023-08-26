#include "Renderer.h"
#include <GL/gl.h>
#include "../Maths/Maths.h"

void Renderer::GetRGB(int hexRGB,byte& r,byte& g,byte& b)
{
	r = (hexRGB>>16) & 0xff;                        // Extracting r,g,b values from hexadecimal
    g = (hexRGB>>8) & 0xff;
    b = hexRGB & 0xff;
}

void Renderer::background(int hexRGB)
{
	byte r,g,b;
	GetRGB(hexRGB,r,g,b);
	background(r,g,b);
}

void Renderer::background(byte r,byte g,byte b)
{
	float R = map(r,0,255,0,1);
	float G = map(g,0,255,0,1);
	float B = map(b,0,255,0,1);
	glClearColor(R,G,B,1.0f);
}

void Renderer::fill(int hexRGB)
{
	byte r,g,b;
	GetRGB(hexRGB,r,g,b);
	fill(r,g,b);
}

void Renderer::fill(byte r,byte g,byte b)
{
	float R = map(r,0,255,0,1);
	float G = map(g,0,255,0,1);
	float B = map(b,0,255,0,1);
	glColor3f(R,G,B);
}

void Renderer::strokeWeight(float w)
{
	glLineWidth(w);
}

void Renderer::plane(float width,float height,GLenum mode)
{
	if(height == 0)
		height = width;

	const float w = 0.5 * width;
	const float h = 0.5 * height;

	glBegin(mode);
		glVertex2f(-w,h);
		glVertex2f(w,h);
		glVertex2f(w,-h);
		glVertex2f(-w,-h);
	glEnd();
}

void Renderer::planeMesh(float width,float height)
{
	plane(width,height,GL_LINE);
}

void Renderer::box(float side,int front,int left,int back,int right,int top,int bottom)
{
	box(side,side,side,front,left,back,right,top,bottom);
}

void Renderer::box(float length,float breadth,float height,int front,int left,int back,int right,int top,int bottom)
{
	if(breadth == 0)
		breadth = length;
	if(height == 0)
		height = length;

	const float l = 0.5 * length;
	const float b = 0.5 * breadth;
	const float h = 0.5 * height;

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
}

void Renderer::boxMesh(float side)
{
	boxMesh(side,side,side);
}

void Renderer::boxMesh(float length,float breadth,float height)
{
	if(breadth == 0)
		breadth = length;
	if(height == 0)
		height = length;

	const float l = 0.5 * length;
	const float b = 0.5 * breadth;
	const float h = 0.5 * height;

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
}
