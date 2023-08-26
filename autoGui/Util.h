#ifndef UTIL_H
#define UTIL_H

#include <iostream>

namespace autoGui
{
	struct Vec2D
	{
		float x,y;
		Vec2D()
		{
			this->x = this->y = 0;
		}
		Vec2D(const float& x,const float& y){
			this->x = x;
			this->y = y;
		}
		Vec2D operator-();
		Vec2D operator+(const Vec2D& vec);
		Vec2D operator+=(const Vec2D& vec);
		Vec2D operator-(const Vec2D& vec);
		Vec2D operator-=(const Vec2D& vec);
		Vec2D operator*(const float& f);
		Vec2D operator*=(const float& f);
		Vec2D operator/(const float& f);
		Vec2D operator/=(const float& f);
		float length();
		Vec2D normalize();
	};

	std::ostream& operator<<(std::ostream& os,Vec2D vec);
}

#endif // UTIL_H
