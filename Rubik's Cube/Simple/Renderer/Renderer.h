#ifndef RENDERER_H
#define RENDERER_H

#include "../Color/Color.h"
#include <GL/gl.h>
#include <GL/glu.h>

class Renderer
{
        protected:
		//Some utility Functions

        float map(float n,float start1,float stop1,float start2,float stop2);
        float InRange(float value,float Min,float Max);

        //Render Functions
        void glbackground(float r,float g,float b);
        void background(int hexRGB);
        void background(float r,float g,float b);
        void fill(int hexRGB);
        void fill(float r,float g,float b);

        //3D Render Functions

        void plane(float width,float height);
        void box(float size);
        void box(float length,float breadth,float height);
        void box(float size,int front,int left,int back,int right,int top,int bottom);
        void box(float length,float breadth,float height,int front,int left,int back,int right,int top,int bottom);
        void boxMesh(float size);
        void boxMesh(float length,float breadth,float height);
        void sphere(float r,int lats = 125,int longs = 125,GLenum mode = GL_TRIANGLE_STRIP);
};

#endif // RENDERER_H
