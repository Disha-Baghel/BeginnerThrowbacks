#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <string>
#include <queue>
#include "Event.h"
#include "../GL/Context.h"

namespace Simple
{
	class Window
	{
	public:
		Window(const uint16_t Width = 800,const uint16_t Height = 600,const std::string WindowTitle = "Window");
		~Window();
		void SetWindowTitle(const std::string Name);
		void SetPos(const uint16_t X, const uint16_t Y) const;
		void SetVisible(const bool visible) const;
		const std::string GetWindowTitle() const;
		void GetMouseState(uint16_t& MouseX,uint16_t& MouseY);
		const bool GetEvent(Event& ev);
		const Context& GetContext();
		void Close() const;
	protected:
		virtual LRESULT WindowEvent(UINT uMsg,WPARAM wParam,LPARAM lParam);
	private:
		static LRESULT CALLBACK WindowEventHandler(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
		const Key::Key_t TranslateKey(const uint16_t code);
	private:
		static BYTE WindowCount;

		HWND hWindow;
		Context* context;

		uint16_t X,Y;
		uint16_t WIDTH,HEIGHT;
		bool focus;
		uint16_t MouseX,MouseY;
		bool mouse[3];
		bool Keys[100];
		std::string WindowTitle;
		std::string WindowClassName;
		std::queue<Event> events;
	};
}

#endif // WINDOW_H
