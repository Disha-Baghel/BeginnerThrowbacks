#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

bool Register(HINSTANCE hInstance)
{
    WNDCLASS wc = { 0 };

    wc.hInstance = hInstance;
    wc.lpszClassName = "Class";
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hIcon = (HICON)LoadIcon(hInstance,IDI_APPLICATION);
    wc.hCursor = (HCURSOR)LoadCursor(hInstance, IDC_ARROW);

    return RegisterClass(&wc);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    if(Register(hInstance))
    {
        HWND window = CreateWindow("Class","It's a Window",
                                   WS_OVERLAPPEDWINDOW,
                                   CW_USEDEFAULT, CW_USEDEFAULT,
                                   640,480,
                                   0,0,hInstance,NULL);
        ShowWindow(window, SW_SHOW);

        MSG msg;

        while(GetMessage(&msg,window,0,0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}
