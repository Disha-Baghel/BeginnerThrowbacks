#ifndef OPENGL_H
#define OPENGL_H

#include "Renderer.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <windows.h>

class OpenGL: protected Renderer
{
	HDC m_hDeviceContext;
	void GLEnable();
protected:
	OpenGL(){}
	void InitGL(HWND hWnd,const UINT width,const UINT height);
	void ResizeGLScene(const UINT width,const UINT height);
	HDC GetDeviceContext() const {return m_hDeviceContext;}
};

#endif // OPENGL_H
