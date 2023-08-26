#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <string>

class Window
{
	HWND m_hWindow;
	std::string m_AppName;
	static UINT m_WindowCount;
protected:
	Window();
	void createWindow(UINT& width,UINT& height);
	virtual LRESULT HandleMessage(UINT uMsg,WPARAM wParam,LPARAM lParam) = 0;

	void SetWindowName(const std::string AppName){
		m_AppName = AppName;
		if(m_hWindow != nullptr)
			SetWindowText(m_hWindow,m_AppName.c_str());
	}

	const HWND& GetWindowHandle() const {return m_hWindow;}

	void showWindow() const
	{
		ShowWindow(m_hWindow,SW_SHOW);
	}
private:
	static LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
};

#endif // WINDOW_H
