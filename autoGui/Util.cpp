#include <cmath>
#include "Util.h"

namespace autoGui
{
	Vec2D Vec2D::operator-()
	{
		return Vec2D(-x,-y);
	}

	Vec2D Vec2D::operator+(const Vec2D& vec)
	{
		return Vec2D(x+vec.x,y+vec.y);
	}

	Vec2D Vec2D::operator+=(const Vec2D& vec)
	{
		*this = *this + vec;
		return *this;
	}

	Vec2D Vec2D::operator-(const Vec2D& vec)
	{
		return Vec2D(x-vec.x,y-vec.y);
	}

	Vec2D Vec2D::operator-=(const Vec2D& vec)
	{
		*this = *this - vec;
		return *this;
	}

	Vec2D Vec2D::operator*(const float& f)
	{
		return Vec2D(x*f,y*f);
	}

	Vec2D Vec2D::operator*=(const float& f)
	{
		*this = *this * f;
		return *this;
	}

	Vec2D Vec2D::operator/(const float& f)
	{
		return Vec2D(x/f,y/f);
	}

	Vec2D Vec2D::operator/=(const float& f)
	{
		*this = *this / f;
		return *this;
	}

	float Vec2D::length()
	{
		return sqrt(x*x + y*y);
	}

	Vec2D Vec2D::normalize()
	{
		return Vec2D(x/length(),y/length());
	}

	std::ostream& operator<<(std::ostream& os,Vec2D vec)
	{
		os<<"[ "<<vec.x<<" , "<<vec.y<<" ]\n";
		return os;
	}
}
