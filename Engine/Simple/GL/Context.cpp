#include "Context.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "../Exception/Exception.h"

namespace Simple
{
	Context::Context(HDC dc,uint16_t Width,uint16_t Height)
	{
		this->hDeviceContext = dc;

		PIXELFORMATDESCRIPTOR pfd;

		pfd.nSize           = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion        = 1;
		pfd.dwFlags         = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType      = PFD_TYPE_RGBA;
		pfd.cColorBits      = 32;
		pfd.cDepthBits      = 24;
		pfd.cStencilBits    = 8;

		int Format = ChoosePixelFormat(dc,&pfd);

		if(!SetPixelFormat(hDeviceContext,Format,&pfd))
			throw Exception("Failed to SetPixel Format","Context.cpp",24);

		hRenderContext = wglCreateContext(hDeviceContext);


		if(!wglMakeCurrent(hDeviceContext,hRenderContext))
			throw Exception("Failed to Make hRenderContext as Current","Context.cpp",30);

		Resize(Width,Height);

		glShadeModel(GL_SMOOTH);
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

		owned = true;
		QueryPerformanceCounter(&TimeOffset);
	}

	Context::~Context()
	{
		if(!owned) return;

		wglMakeCurrent(hDeviceContext,NULL);
		wglDeleteContext(hRenderContext);
	}

	void Context::Activate()
	{
		if( owned && wglGetCurrentContext() != hRenderContext) wglMakeCurrent(hDeviceContext,hRenderContext);
	}

	void Context::Present()
	{
		SwapBuffers(hDeviceContext);
	}

	const float Context::Time()
	{
		LARGE_INTEGER time,freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		return ((time.QuadPart - TimeOffset.QuadPart) * 1000/ freq.QuadPart) / 1000.0f;
	}

	void Context::Resize(uint16_t Width,uint16_t Height)
	{
		glViewport(0,0,Width,Height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(45,(GLdouble)Width/(GLdouble)Height,1.0f,1000.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}
