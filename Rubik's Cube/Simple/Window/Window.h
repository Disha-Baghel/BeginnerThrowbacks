#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>

class Window
{
    public:
        Window(){}
        Window(PCSTR windowName,PCSTR className);
        virtual ~Window();

    protected:
        void Create(UINT width,UINT height);
        virtual LRESULT HandleMessage(UINT uMsg,WPARAM wParam,LPARAM lParam) = 0;
        HWND            m_hWindow;

        void SetWindowTitle(LPCSTR title)
        {
                SetWindowText(m_hWindow,title);
        }

    private:
        HINSTANCE       m_hInstance;
        UINT            m_ClientWidth;
        UINT            m_ClientHeight;
        DWORD           m_WindowStyle;
        PCSTR           m_WindowName;
        PCSTR           m_ClassName;

        static LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
};

#endif // WINDOW_H
