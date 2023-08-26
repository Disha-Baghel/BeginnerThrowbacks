#include "Canvas.h"
#include "../Exception/Exception.h"

int Canvas::CanvasCount = 0;

Canvas::Canvas(UINT width,UINT height,bool GL):Window("Application",("CanvasClass" + std::to_string(CanvasCount++)).c_str())
{
    WIDTH = width;
    HEIGHT = height;
    this->EnableGL = GL;
    this->StaticCanvas = false;

    try
    {
        Create(WIDTH,HEIGHT);
        if(GL)
            InitGL(m_hWindow,WIDTH,HEIGHT);
    }catch(Exception& excep)
    {
        excep.what();
    }
}

void Canvas::ShowCanvas()
{
    ShowWindow(m_hWindow,SW_SHOW);
    SetForegroundWindow(m_hWindow);
    SetFocus(m_hWindow);
}

int Canvas::Run()
{
    bool DrawnOnce = false;
    MSG msg = { };

    ShowCanvas();

    while(msg.message != WM_QUIT)
    {
        if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
        {
            DispatchMessage(&msg);
            TranslateMessage(&msg);
        }
        else if(!StaticCanvas || !DrawnOnce)
        {
            Update();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();
            glTranslatef(0,0,-3.0);
            Render();
            SwapBuffers(m_hDeviceContext);

            if(StaticCanvas)
            {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                SwapBuffers(m_hDeviceContext);
                DrawnOnce = true;
            }
        }
    }

    return static_cast<int>(msg.wParam);
}

LRESULT Canvas::HandleMessage(UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    KeyCode = 0;
    switch(uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_SIZE:
        WIDTH   = LOWORD(lParam);
        HEIGHT  = HIWORD(lParam);
        ReSizeGLScene(WIDTH,HEIGHT);
        break;
    case WM_KEYDOWN:
        KeyCode = wParam;
        break;
    default:
        return DefWindowProc(m_hWindow,uMsg,wParam,lParam);
    }

    return 0;
}

bool Canvas::KeyDown(int key)
{
    bool prevState = prevKeyboardState[key];
    prevKeyboardState[key] = GetAsyncKeyState(key) & 0x8000;
    return (prevKeyboardState[key] && !prevState);
}

bool Canvas::KeyIsDown(int key)
{
    return GetAsyncKeyState(key) & 0x8000;
}
