#include "Window.h"
#include "../Exception/Exception.h"

LRESULT CALLBACK Window::WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    Window* pThis = nullptr;

    if(uMsg == WM_NCCREATE)
    {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pThis = reinterpret_cast<Window*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hWnd,GWLP_USERDATA,(LONG_PTR)pThis);
        pThis->m_hWindow = hWnd;
    }else{
        pThis = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd,GWLP_USERDATA));
    }

    if(pThis)
        return pThis->HandleMessage(uMsg,wParam,lParam);
    else
        return DefWindowProc(hWnd,uMsg,wParam,lParam);
    return 0;
}

Window::Window(PCSTR windowName,PCSTR className)
{
    m_hWindow       = NULL;
    m_ClientWidth   = CW_USEDEFAULT;
    m_ClientHeight  = CW_USEDEFAULT;
    m_WindowName    = windowName;
    m_ClassName     = className;

    m_WindowStyle   = WS_OVERLAPPEDWINDOW;
}

Window::~Window()
{
    //Shutdown();
}

void Window::Create(UINT width,UINT height)
{
    if(width != 0 && height != 0)
    {
        m_ClientWidth   = width;
        m_ClientHeight  = height;
    }

    WNDCLASS wc = { };

    wc.lpfnWndProc      = WndProc;
    wc.hInstance        = GetModuleHandle(NULL);
    wc.lpszClassName    = m_ClassName;

    if(!RegisterClass(&wc))
        throw Exception("COULD NOT REGISTER CLASS.",SHOW_SHUTDOWN);

    m_hWindow = CreateWindow(m_ClassName,
                             m_WindowName,
                             WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT,CW_USEDEFAULT,
                             m_ClientWidth,m_ClientHeight,
                             NULL,
                             NULL,
                             GetModuleHandle(NULL),
                             this);
    if(!m_hWindow)
        throw Exception("FAILED TO CREATE WINDOW.",SHOW_SHUTDOWN);
}
