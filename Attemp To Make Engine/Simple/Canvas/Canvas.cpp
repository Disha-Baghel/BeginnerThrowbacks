#include "Canvas.h"
#include "../Error/Error.h"
#include "../Timer/Timer.h"

void Canvas::CreateCanvas(const UINT width,const UINT height)
{
	WIDTH = width;
	HEIGHT = height;

	try{
		createWindow(WIDTH,HEIGHT);
		InitGL(GetWindowHandle(),WIDTH,HEIGHT);
		Timer::GetInstance()->Init();
	}catch(Error& Err){
		Err.what();
	}
}

int Canvas::Run()
{
	MSG msg;

	showWindow();

	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}else
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();

			Update(Timer::GetInstance()->GetDeltaTime());
			Render();

			SwapBuffers(GetDeviceContext());
		}
		Timer::GetInstance()->Tick();
	}

	return static_cast<int>(msg.wParam);
}

LRESULT Canvas::HandleMessage(UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_SIZE:
		WIDTH = LOWORD(lParam);
		HEIGHT = HIWORD(lParam);
		ResizeGLScene(WIDTH,HEIGHT);
		break;
	case WM_MOUSEMOVE:
		MouseX = (int)(short)LOWORD(lParam);
		MouseY = (int)(short)HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		KeyDown = wParam;
		break;
	case WM_KEYUP:
		KeyDown = 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(GetWindowHandle(),uMsg,wParam,lParam);
	}
	Camera::Callback(KeyDown,MouseX,MouseY);

	return 0;
}

UINT Canvas::GetTicks()
{
	return  Timer::GetInstance()->GetTicks();
}

bool Canvas::KeyClicked(BYTE key)
{
	bool prevState = Keys[key];
	Keys[key] = IsKeyDown(key);
	return (Keys[key] && !prevState);
}

bool Canvas::IsKeyDown(BYTE key)
{
	return GetKeyState(key) & 0x8000;
}
