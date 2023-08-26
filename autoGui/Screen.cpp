#include <windows.h>
#include "Screen.h"

namespace autoGui
{
	namespace Screen
	{
		const Vec2D size()
		{
			int x = GetSystemMetrics(SM_CXFULLSCREEN);
			int y = GetSystemMetrics(SM_CYFULLSCREEN);
			return Vec2D(x,y);
		}
	}
}
