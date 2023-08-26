#include "Window.h"
#include <string>
#include <iostream>

namespace Scratch
{
    short Window::m_WindowCount = 0;

    LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        Window* pThis = nullptr;

        if(uMsg == WM_NCCREATE)
        {
            CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
            pThis = reinterpret_cast<Window*>(pCreate->lpCreateParams);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
            pThis->m_WindowHandle = hWnd;
        }
        else
            pThis = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

        if(pThis)
            return pThis->HandleEvent(uMsg,wParam,lParam);
        else
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    Window::Window(const unsigned short& width, const unsigned short& height, const char* const& title) :
        m_Width(width),
        m_Height(height),
        m_Title(title)
    {
        m_WindowCount++;
        MakeWindow();
        m_DeviceContext = GetDC(m_WindowHandle);
    }

    Window::~Window()
    {
        DestroyWindow(m_WindowHandle);
        DeleteDC(m_DeviceContext);
    }

    void Window::MakeWindow()
    {
        WNDCLASS wc = {};

        HINSTANCE hInstance = GetModuleHandle(NULL);
        const char* const className = ("Class " + std::to_string(m_WindowCount)).c_str();

        wc.hInstance = hInstance;
        wc.lpfnWndProc = WindowProc;
        wc.lpszClassName = className;
        wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.style = CS_OWNDC;

        if(!RegisterClass(&wc))
        {
            std::cout << "Failed to register class.";
            exit(0);
        }

        m_WindowHandle = CreateWindow(className,
                                      m_Title,
                                      WS_OVERLAPPEDWINDOW,
                                      CW_USEDEFAULT,CW_USEDEFAULT,
                                      m_Width,m_Height,
                                      NULL,
                                      NULL,
                                      hInstance,
                                      this);

        if(!m_WindowHandle)
        {
            std::cout << "Failed to create Window.";
            exit(0);
        }

        ShowWindow(m_WindowHandle,SW_SHOW);
    }

    LRESULT Window::HandleEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        Event event;
        event.type = UNKNOWN;

        switch(uMsg)
        {
        case WM_QUIT:
        case WM_CLOSE:
            event.type = QUIT;
            break;
        default:
            return DefWindowProc(m_WindowHandle, uMsg, wParam, lParam);
        }

        events.push(event);
        return 0;
    }

    bool Window::GetEvent(Event& event)
    {
        MSG msg;
        while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if(events.size() <= 0)
            return false;

        event = events.back();
        events.pop();

        return true;
    }
}
