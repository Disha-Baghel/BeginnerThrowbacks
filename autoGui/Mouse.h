#ifndef MOUSE_H
#define MOUSE_H

#include "Util.h"

namespace autoGui{

	namespace Mouse
	{
		const Vec2D position();
		const Vec2D size();
		bool onScreen(const int& x,const int& y);

		void moveTo(const int& x,const int& y,const float& time = 0);
		void moveRel(const int& xOffset,const int& yOffset);

		void dragTo(const int& x,const int& y);
		void dragRel(const int& xOffset,const int& yOffset);

		void click(const int& count=1);
		void click(const int& x,const int& y,const int& count=1);

		void mouseDown(const int& x,const int& y);
		void mouseUp(const int& x,const int& y);
	}
}

#endif // MOUSE_H
