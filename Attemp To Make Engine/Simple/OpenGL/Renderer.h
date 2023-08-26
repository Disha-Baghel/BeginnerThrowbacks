#ifndef RENDERER_H
#define RENDERER_H

#include "../Color.h"
#include <GL/gl.h>

using byte = unsigned char;

class Renderer
{
protected:
	void GetRGB(int hexRGB,byte& r,byte& g,byte& b);
	void background(int hexRGB);
	void background(byte r,byte g,byte b);
	void fill(int hexRGB);
	void fill(byte r,byte g,byte b);
	void strokeWeight(float w);

	void plane(float width,float height = 0,GLenum mode = GL_QUADS);
	void planeMesh(float width,float height = 0);

	void box(float side,int front = COLOR_RED,int left = COLOR_GREEN,int back = COLOR_ORANGE,int right = COLOR_BLUE,int top = COLOR_WHITE,int bottom = COLOR_YELLOW);
	void box(float length,float breadth,float height,int front = COLOR_RED,int left = COLOR_GREEN,int back = COLOR_ORANGE,int right = COLOR_BLUE,int top = COLOR_WHITE,int bottom = COLOR_YELLOW);
	void boxMesh(float side);
	void boxMesh(float length,float breadth,float height);
};

#endif // RENDERER_H
