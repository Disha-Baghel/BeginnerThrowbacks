#include "Window.h"
#include <windowsx.h>
#include "../Exception/Exception.h"

namespace Simple
{
	BYTE Window::WindowCount = 0;

	Window::Window(const uint16_t Width,const uint16_t Height,const std::string WindowTitle)
	{
		WNDCLASS wc = { 0 };

		WindowClassName		= "Class " + std::to_string(WindowCount+1) + WindowTitle;

		wc.lpfnWndProc 		= WindowEventHandler;
		wc.hInstance   		= GetModuleHandle(NULL);
		wc.hIcon			= LoadIcon(NULL,IDI_APPLICATION);
		wc.hCursor			= LoadCursor(NULL,IDC_ARROW);
		wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszClassName	= WindowClassName.c_str();
		wc.style			= CS_OWNDC;

		if(!RegisterClass(&wc))
			throw Exception("Failed to Register Window.","Window.cpp",23);

		hWindow = CreateWindow(	WindowClassName.c_str(),
								WindowTitle.c_str(),
								WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT,CW_USEDEFAULT,
								Width,Height,
								NULL,
								NULL,
								GetModuleHandle(NULL),
								this);

		if(!hWindow)
			throw Exception("Failed to Create Window.","Window.cpp",36);

		SetVisible(true);

		WindowCount++;
		this->WindowTitle = WindowTitle;
		this->WIDTH = Width;
		this->HEIGHT = Height;
		this->MouseX = 0;
		this->MouseY = 0;
		context = nullptr;
	}

	Window::~Window()
	{
		DestroyWindow(hWindow);
		UnregisterClass(WindowClassName.c_str(),GetModuleHandle(NULL));
	}

	LRESULT CALLBACK Window::WindowEventHandler(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
	{
		Window* pThis = nullptr;

		if(uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
			pThis = reinterpret_cast<Window*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hWnd,GWLP_USERDATA,(LONG_PTR)pThis);
			pThis->hWindow = hWnd;
		}
		else
			pThis = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd,GWLP_USERDATA));

		if(pThis)
			return pThis->WindowEvent(uMsg,wParam,lParam);
		else
			return DefWindowProc(hWnd,uMsg,wParam,lParam);
	}

	LRESULT Window::WindowEvent(UINT uMsg,WPARAM wParam,LPARAM lParam)
	{
		Event ev;
		ev.Type = Event::Unkown;

		switch(uMsg)
		{
		case WM_CLOSE:
			Close();
			ev.Type = Event::Close;
			break;

		case WM_SIZE:

			WIDTH = GET_X_LPARAM( lParam );
			HEIGHT = GET_Y_LPARAM( lParam );

			if(context)
				context->Resize(WIDTH,HEIGHT);

			if(events.empty())
			{
				ev.Type = Event::Resize;
				ev.Window.Width = WIDTH;
				ev.Window.height = HEIGHT;
			} else if( events.back().Type == Event::Resize){
				events.back().Window.Width = WIDTH;
				events.back().Window.height = HEIGHT;
			}
			break;
		case WM_MOVE:
			RECT rect;
			GetWindowRect(hWindow,&rect);
			X = rect.left;
			Y = rect.top;

			if(events.empty())
			{
				ev.Type = Event::Move;
				ev.Window.X = X;
				ev.Window.Y = Y;
			}else if(events.back().Type == Event::Move){
				events.back().Window.X = X;
				events.back().Window.Y = Y;
			}
			break;
		case WM_ACTIVATE:
			if(wParam == WA_INACTIVE)
			{
				ev.Type = Event::Blur;
				focus = false;
			}else{
				ev.Type = Event::Focus;
				focus = true;
			}
			break;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			ev.Type = Event::KeyDown;
			ev.Key.Code = TranslateKey( wParam );
			ev.Key.Alt = HIWORD(GetAsyncKeyState(VK_MENU) != 0);
			ev.Key.Control = HIWORD(GetAsyncKeyState(VK_CONTROL != 0));
			ev.Key.Shift = HIWORD(GetAsyncKeyState(VK_SHIFT) != 0);
			break;

		case WM_KEYUP:
		case WM_SYSKEYUP:
			ev.Type = Event::KeyUp;
			ev.Key.Code = TranslateKey( wParam );
			ev.Key.Alt = HIWORD(GetAsyncKeyState(VK_MENU) != 0);
			ev.Key.Control = HIWORD(GetAsyncKeyState(VK_CONTROL != 0));
			ev.Key.Shift = HIWORD(GetAsyncKeyState(VK_SHIFT) != 0);
			break;

		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
			MouseX = GET_X_LPARAM(lParam);
			MouseY = GET_Y_LPARAM(lParam);

			if(uMsg == WM_LBUTTONDOWN) ev.Mouse.Button = MouseButton::Left;
			else if(uMsg == WM_RBUTTONDOWN) ev.Mouse.Button = MouseButton::Right;
			else if(uMsg == WM_MBUTTONDOWN) ev.Mouse.Button = MouseButton::Middle;

			ev.Type = Event::MouseDown;
			ev.Mouse.X = MouseX;
			ev.Mouse.Y = MouseY;

			mouse[ev.Mouse.Button] = true;
			break;

		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
			MouseX = GET_X_LPARAM(lParam);
			MouseY = GET_Y_LPARAM(lParam);

			if(uMsg == WM_LBUTTONUP) ev.Mouse.Button = MouseButton::Left;
			else if(uMsg == WM_RBUTTONUP) ev.Mouse.Button = MouseButton::Right;
			else if(uMsg == WM_MBUTTONDOWN) ev.Mouse.Button = MouseButton::Middle;

			ev.Type = Event::MouseUp;
			ev.Mouse.X = MouseX;
			ev.Mouse.Y = MouseY;

			mouse[ev.Mouse.Button] = false;
			break;

		case WM_MOUSEWHEEL:
			MouseX = GET_X_LPARAM(lParam);
			MouseY = GET_Y_LPARAM(lParam);

			ev.Type = Event::MouseWheel;
			ev.Mouse.Delta = GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? 1 : -1;
			ev.Mouse.X = MouseX;
			ev.Mouse.Y = MouseY;
			break;

		case WM_MOUSEMOVE:
			MouseX = GET_X_LPARAM(lParam);
			MouseY = GET_Y_LPARAM(lParam);

			ev.Type = Event::MouseMove;
			ev.Mouse.X = MouseX;
			ev.Mouse.Y = MouseY;
			break;
		default:
			return DefWindowProc(hWindow,uMsg,wParam,lParam);
		}

		if( ev.Type != Event::Unkown)
			events.push(ev);

		return 0;
	}

	const Key::Key_t Window::TranslateKey(const uint16_t code)
	{
		switch(code)
		{
			case VK_SHIFT		: return Key::Shift;
			case VK_MENU		: return Key::Alt;
			case VK_CONTROL		: return Key::Control;
			case VK_OEM_1		: return Key::Semicolon;
			case VK_OEM_2		: return Key::Slash;
			//case VK_OEM_PLUS	: return Key::Equals;
			//case VK_OEM_MINUS	: return Key::Hyphen;
			case VK_OEM_4		: return Key::LeftBracket;
			case VK_OEM_6		: return Key::RightBracket;
			//case VK_OEM_COMMA	: return Key::Comma;
			//case VK_OEM_PERIOD	: return Key::Period;
			case VK_OEM_7		: return Key::Quote;
			case VK_OEM_5		: return Key::Backslash;
			case VK_OEM_3		: return Key::Tilde;
			case VK_ESCAPE		: return Key::Escape;
			case VK_SPACE		: return Key::Space;
			case VK_RETURN		: return Key::Enter;
			case VK_BACK		: return Key::Backspace;
			case VK_TAB			: return Key::Tab;
			case VK_PRIOR		: return Key::PageUp;
			case VK_NEXT		: return Key::PageDown;
			case VK_END			: return Key::End;
			case VK_HOME		: return Key::Home;
			case VK_INSERT		: return Key::Insert;
			case VK_DELETE		: return Key::Delete;
			case VK_ADD			: return Key::Add;
			case VK_SUBTRACT	: return Key::Subtract;
			case VK_MULTIPLY	: return Key::Multiply;
			case VK_DIVIDE		: return Key::Divide;
			case VK_PAUSE		: return Key::Pause;
			case VK_LEFT		: return Key::Left;
			case VK_RIGHT		: return Key::Right;
			case VK_UP			: return Key::Up;
			case VK_DOWN		: return Key::Down;

			default:
				if( code >= VK_F1 && code <= VK_F12)
					return (Key::Key_t)(Key::F1 + code - VK_F1);
				else if(code >= VK_NUMPAD0 && code <= VK_NUMPAD9)
					return (Key::Key_t)(Key::Numpad0 + code - VK_NUMPAD0);
				else if(code >= 'A' && code <= 'Z')
					return (Key::Key_t)(Key::A + code - 'A');
				else if(code >= '0' && code <= '9')
					return (Key::Key_t)(Key::Num0 + code - '0');
		}

		return Key::Unknown;
	}

	void Window::SetWindowTitle(const std::string WindowTitle)
	{
		this->WindowTitle = WindowTitle;
		SetWindowText(hWindow,WindowTitle.c_str());
	}

	void Window::SetPos(const uint16_t X,const uint16_t Y) const
	{
		SetWindowPos(hWindow,NULL,X,Y,0,0,SWP_NOSIZE | SWP_NOZORDER);
	}

	void Window::SetVisible(const bool visible) const
	{
		ShowWindow(hWindow, visible? SW_SHOW: SW_HIDE);
	}

	const std::string Window::GetWindowTitle() const
	{
		return this->WindowTitle;
	}

	void Window::GetMouseState(UINT16& MouseX,UINT16& MouseY)
	{
		this->MouseX = MouseX;
		this->MouseY = MouseY;
	}

	const bool Window::GetEvent(Event& ev)
	{
		MSG msg;
		while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if( events.empty()) return false;

		ev = events.front();
		events.pop();

		return true;
	}

	const Context& Window::GetContext()
	{
		if(context)
			return *context;
		else
			return *( context = new Context( GetDC(hWindow), WIDTH, HEIGHT ) );
	}

	void Window::Close() const
	{
		CloseWindow(hWindow);
	}
}
