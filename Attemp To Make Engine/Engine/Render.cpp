#include "GLApp.h"

//Point

void GLApp::DrawPoint(GLfloat x,GLfloat y,GLfloat z)
{
    Vec3D v[1] = {x,y,z};
    DrawPoints(v,1);
}

void GLApp::DrawPoints(Vec3D v[],int Count)
{
    glBegin(GL_POINTS);

        for(int i=0;i<Count;i++)
        {
            glVertex3f(v[i].x,v[i].y,v[i].z);
        }

    glEnd();
}

//Line

void GLApp::DrawLine(GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2)
{
    Vec3D v1[1] = {x1,y1,z1};
    Vec3D v2[1] = {x2,y2,z2};
    DrawLines(v1,v2,1);
}

void GLApp::DrawLines(Vec3D v1[],Vec3D v2[],int Count)
{
    glBegin(GL_LINES);

        for(int i=0;i<Count;i++)
        {
            glVertex3f(v1[i].x,v1[i].y,v1[i].z);
            glVertex3f(v2[i].x,v2[i].y,v2[i].z);
        }

    glEnd();
}
