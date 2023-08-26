#include "OpenGL.h"
#include "../Exception/Exception.h"

GLvoid OpenGL::ReSizeGLScene(GLsizei width,GLsizei height){
    if(height == 0){
        height = 1;
    }

    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGL::InitGL(HWND hWindow,GLsizei width,GLsizei height)
{
    m_hDeviceContext = GetDC(hWindow);

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
        throw Exception("FAILED TO SET PIXEL FORMAT.",SHOW_SHUTDOWN);

    m_hRenderContext = wglCreateContext(m_hDeviceContext);

    if(!wglMakeCurrent(m_hDeviceContext,m_hRenderContext))
        throw Exception("FAILED TO CREATE AND ACTIVATE RENDER CONTEXT.",SHOW_SHUTDOWN);

    ReSizeGLScene(width,height);

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}
