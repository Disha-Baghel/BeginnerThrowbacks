#include "GLApp.h"

namespace
{
    GLApp* g_pApp = NULL;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
    if(g_pApp)
        return g_pApp->MsgProc(hWnd,msg,wParam,lParam);
    else
        return DefWindowProc(hWnd,msg,wParam,lParam);
}

GLApp::GLApp(void)
{
    m_hAppInstance      = GetModuleHandle(NULL);
    m_hAppWnd           = NULL;
    m_hDevContext       = NULL;
    m_hRenderContext    = NULL;
    m_AppTitle          = "OPENGL APPLICATION";
    m_WindowStyle       = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
    g_pApp              = this;
}

void GLApp::CreateCanvas(int width,int height)
{
    m_ClientWidth      = width;
    m_ClientHeight     = height;
    Init();
}

GLApp::~GLApp()
{

}

GLvoid GLApp::ReSizeGlScene(GLsizei width,GLsizei height){
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

int GLApp::Run()
{
    __int64 prevTime = 0;
    QueryPerformanceCounter((LARGE_INTEGER*)&prevTime);

    __int64 countPerSec = 0;
    QueryPerformanceFrequency((LARGE_INTEGER*)&countPerSec);
    float secondsPerCount = 1.0f / countPerSec;

    MSG msg = {0};

    Setup();

    while(msg.message != WM_QUIT)
    {
        if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            __int64 curTime = 0;
            QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
            float deltaTime = (curTime - prevTime) * secondsPerCount;

            Update(deltaTime);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();
            Render();

            CalculateFPS(deltaTime);

            SwapBuffers(m_hDevContext);

            prevTime = curTime;
        }
    }

    Shutdown();

    return static_cast<int>(msg.wParam);
}

bool GLApp::InitWindow()
{
    WNDCLASSEX wcex;
    ZeroMemory(&wcex,sizeof(WNDCLASSEX));

    wcex.cbSize             = sizeof(WNDCLASSEX);
    wcex.cbClsExtra         = 0;
    wcex.cbWndExtra         = 0;
    wcex.style              = CS_HREDRAW | CS_VREDRAW;
    wcex.hInstance          = m_hAppInstance;
    wcex.hbrBackground      = (HBRUSH)GetStockObject(NULL_BRUSH);
    wcex.hIcon              = LoadIcon(m_hAppInstance,IDI_APPLICATION);
    wcex.hCursor            = LoadCursor(m_hAppInstance,IDC_ARROW);
    wcex.lpfnWndProc        = WndProc;
    wcex.lpszClassName      = "GLAPPCLASS";
    wcex.lpszMenuName       = NULL;
    wcex.hIconSm            = LoadIcon(m_hAppInstance,IDI_APPLICATION);

    if(!RegisterClassEx(&wcex))
        return OutErrorMsg("FAILED TO REGISTER CLASS");

    RECT r = {0,0,(LONG)m_ClientWidth,(LONG)m_ClientHeight};
    AdjustWindowRect(&r,m_WindowStyle,FALSE);
    int width   = r.right - r.left;
    int height  = r.bottom - r.top;
    int x = GetSystemMetrics(SM_CXSCREEN/2 - width/2);
    int y = GetSystemMetrics(SM_CYSCREEN/2 - height/2);

    m_hAppWnd = CreateWindow("GLAPPCLASS",
                             m_AppTitle,
                             m_WindowStyle,
                             x,y,
                             width,height,
                             NULL,
                             NULL,
                             m_hAppInstance,
                             NULL);

    if(!m_hAppWnd)
        return OutErrorMsg("FAILED TO CREATE WINDOW");

    return true;
}

bool GLApp::InitGL()
{
    m_hDevContext = GetDC(m_hAppWnd);
    PIXELFORMATDESCRIPTOR pfd;
    ZeroMemory(&pfd,sizeof(PIXELFORMATDESCRIPTOR));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    int format = ChoosePixelFormat(m_hDevContext,&pfd);
    if(!SetPixelFormat(m_hDevContext,format,&pfd))
        return OutErrorMsg("FAILED TO SET PIXEL FORMAT");

    m_hRenderContext = wglCreateContext(m_hDevContext);
    if(!wglMakeCurrent(m_hDevContext,m_hRenderContext))
        return OutErrorMsg("FAILED TO CREATE AND ACTIVATE RENDER CONTEXT");

    ShowWindow(m_hAppWnd,SW_SHOW);
    SetForegroundWindow(m_hAppWnd);
    SetFocus(m_hAppWnd);
    ReSizeGlScene(m_ClientWidth,m_ClientHeight);

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

    return true;
}

bool GLApp::Init()
{
    if(!InitWindow()) return false;
    if(!InitGL()) return false;

    return true;
}

LRESULT GLApp::MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
    switch(msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd,msg,wParam,lParam);
    }

    return 0;
}

void GLApp::CalculateFPS(float dt)
{
    static float elapsed = 0;
    static float frameCnt = 0;

    elapsed += dt;
    frameCnt++;
    if(elapsed >= 1.0f)
    {
        m_FPS = (float)frameCnt;
        std::stringstream ss;
        ss<<m_AppTitle<<" FPS: "<<m_FPS<<" "<<
            glGetString(GL_VENDOR)<<" "<<glGetString(GL_RENDERER)<<" "<<glGetString(GL_VERSION);
         SetWindowText(m_hAppWnd,ss.str().c_str());

        elapsed = 0;
        frameCnt = 0;
    }
}

void GLApp::Shutdown()
{
    if(m_hRenderContext){
        if(!wglMakeCurrent(NULL,NULL)){
            OutErrorMsg("Release of DC And RC Failed.");
        }
        if(!wglDeleteContext(m_hRenderContext)){
            OutErrorMsg("Release Rendering Context Failed.");
        }
        else
            m_hRenderContext = NULL;
    }
}
