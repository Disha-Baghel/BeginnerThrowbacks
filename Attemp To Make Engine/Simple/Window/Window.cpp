#include "Window.h"
#include "../Error/Error.h"

LRESULT CALLBACK Window::WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    Window* pThis = nullptr;

    if(uMsg == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		pThis = reinterpret_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd,GWLP_USERDATA,(LONG_PTR)pThis);
		pThis->m_hWindow = hWnd;
	}
	else
	{
		pThis = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd,GWLP_USERDATA));
	}

	if(pThis)
		return pThis->HandleMessage(uMsg,wParam,lParam);
	else
		return DefWindowProc(hWnd,uMsg,wParam,lParam);
	return 0;
}

UINT Window::m_WindowCount = 0;

Window::Window()
{
	m_hWindow 	= NULL;
	m_AppName 	= "Application";
}

void Window::createWindow(UINT& width,UINT& height)
{
	width = (width>0)?width:1;
	height = (height>0)?height:1;

	WNDCLASS wc;
	ZeroMemory(&wc,sizeof(WNDCLASS));

	const char* ClassName 	= ("Class" + std::string(std::to_string(m_WindowCount+1))).c_str();
	wc.hInstance			= GetModuleHandle(NULL);
	wc.lpszClassName		= ClassName;
	wc.lpfnWndProc			= WndProc;

	if(!RegisterClass(&wc))
		throw Error("Failed to Register Window.",Err_ShutDown);

	m_hWindow = CreateWindow(ClassName,
							m_AppName.c_str(),
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,CW_USEDEFAULT,
							width,height,
							NULL,
							NULL,
							wc.hInstance,
							this);

	if(m_hWindow == NULL)
		throw Error("Failed to Create Window.",Err_ShutDown);

	m_WindowCount++;
}
