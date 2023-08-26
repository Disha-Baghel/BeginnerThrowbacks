#include <windows.h>
#include "Mouse.h"
#include "Time.h"

namespace autoGui{

	namespace Mouse
	{
		const Vec2D position()
		{
			POINT p;
			GetCursorPos(&p);
			return Vec2D(p.x,p.y);
		}

		bool onScreen(const int& x,const int& y)
		{
			Vec2D vec = position();
			return (x >= 0 && x <= vec.x) && (y >= 0 && y <= vec.y);
		}

		void moveTo(const int& x,const int& y,const float& time)
		{
			if(time <= 0)
				SetCursorPos(x,y);
			else
			{

				// Not an efficient function. Need to find something else
				// Will Do later

				Vec2D Cur = position();
				float len = (Cur - Vec2D(x,y)).length();
				Vec2D Dir = (Cur - Vec2D(x,y)).normalize();
				float dt = time/len;
				while(len-- > 0)
				{
					Cur -= Dir;
					SetCursorPos(Cur.x,Cur.y);
					Time::WaitNano(Time::SecondsToNano(dt));
				}
			}
		}

		void moveRel(const int& xOffset,const int& yOffset)
		{
			Vec2D pos = position();
			SetCursorPos(pos.x + xOffset, pos.y + yOffset);
		}

		void dragTo(const int& x,const int& y)
		{
			mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
			moveTo(x,y);
			mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
		}

		void dragRel(const int& xOffset,const int& yOffset)
		{
			mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
			moveRel(xOffset,yOffset);
			mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
		}

		void click(const int& count)
		{
			for(int i=0;i<count;i++)
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
				mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
			}
		}

		void click(const int& x,const int& y,const int& count)
		{
			moveTo(x,y);
			click(count);
		}

		void mouseDown(const int& x,const int& y)
		{
			moveTo(x,y);
			mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
		}

		void mouseUp(const int& x,const int& y)
		{
			moveTo(x,y);
			mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
		}
	}
}
