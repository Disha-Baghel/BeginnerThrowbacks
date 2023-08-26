#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <queue>
#include "../Event/Event.h"

namespace Scratch
{
    class Window
    {
    public:
        Window(const unsigned short& width, const unsigned short& height, const char* const& title);
        bool GetEvent(Event& event);
        virtual ~Window();
    protected:
        void MakeWindow();
        virtual LRESULT HandleEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);
    private:
        static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    private:
        short m_Width;
        short m_Height;
        const char* m_Title;

        static short m_WindowCount;

        HWND m_WindowHandle;
        HDC  m_DeviceContext;

        std::queue<Event> events;
    };
}

#endif // WINDOW_H
