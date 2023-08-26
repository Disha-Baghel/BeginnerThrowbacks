#include "OpenGL.h"
#include "../Error/Error.h"

void OpenGL::ResizeGLScene( UINT width, UINT height)
{
	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45,(GLdouble)width/(GLdouble)height,1.0f,1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGL::InitGL(HWND hWnd,const UINT width,const UINT height)
{
	m_hDeviceContext = GetDC(hWnd);

	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd,sizeof(PIXELFORMATDESCRIPTOR));

    pfd.nSize           = sizeof(pfd);
    pfd.nVersion        = 1;
    pfd.dwFlags         = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType      = PFD_TYPE_RGBA;
    pfd.cColorBits      = 32;
    pfd.cDepthBits      = 24;
    pfd.cStencilBits    = 8;

    int format = ChoosePixelFormat(m_hDeviceContext,&pfd);

    if(!SetPixelFormat(m_hDeviceContext,format,&pfd))
        throw Error("FAILED TO SET PIXEL FORMAT.",Err_ShutDown);

    HGLRC hRenderContext = wglCreateContext(m_hDeviceContext);

    if(!wglMakeCurrent(m_hDeviceContext,hRenderContext))
        throw Error("FAILED TO CREATE AND ACTIVATE RENDER CONTEXT.",Err_ShutDown);

	ResizeGLScene(width,height);

	GLEnable();
}

void OpenGL::GLEnable()
{
	glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}
