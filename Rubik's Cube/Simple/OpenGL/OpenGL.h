#ifndef OPENGL_H
#define OPENGL_H

#include <windows.h>
#include "Renderer.h"

class OpenGL: public Renderer
{
    protected:
        void InitGL(HWND hWindow,GLsizei width,GLsizei height);
        GLvoid ReSizeGLScene(GLsizei width,GLsizei height);

        HDC     m_hDeviceContext;
    private:
        HGLRC   m_hRenderContext;

};

#endif // OPENGL_H
