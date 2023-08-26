#include "MathsVector.h"
#include <cmath>

float Vec2d::mag()
{
    return sqrt(x*x + y*y);
}

void Vec2d::normalize()
{
    float d = mag();
    x /= d;
    y /= d;
}

void Vec2d::limit(float m)
{
    if(mag() > m)
    {
        normalize();
        x *= m;
        y *= m;
    }
}

Vec2d operator+(Vec2d v1,Vec2d &v2)
{
    v1.x = v1.x + v2.x;
    v1.y = v1.y + v2.y;
    return v1;
}

void operator+=(Vec2d &v1,Vec2d &v2)
{
    v1.x = v1.x + v2.x;
    v1.y = v1.y + v2.y;
}

Vec2d operator-(Vec2d v1,Vec2d &v2)
{
    v1.x = v1.x - v2.x;
    v1.y = v1.y - v2.y;
    return v1;
}

void operator-=(Vec2d &v1,Vec2d &v2)
{
    v1.x = v1.x - v2.x;
    v1.y = v1.y - v2.y;
}

Vec2d operator*(Vec2d v1,Vec2d &v2)
{
    v1.x = v1.x * v2.x;
    v1.y = v1.y * v2.y;
    return v1;
}

void operator*=(Vec2d &v1,Vec2d &v2)
{
    v1.x = v1.x * v2.x;
    v1.y = v1.y * v2.y;
}

Vec2d operator-(Vec2d v)
{
    v.x = -v.x;
    v.y = -v.y;
    return v;
}

Vec2d operator*(Vec2d v1,float m)
{
    v1.x *= m;
    v1.y *= m;
    return v1;
}

void operator*=(Vec2d &v1,float m)
{
    v1.x *= m;
    v1.y *= m;
}

Vec2d operator/(Vec2d v1,float m)
{
    v1.x /= m;
    v1.y /= m;
    return v1;
}

void operator/=(Vec2d &v1,float m)
{
    v1.x /= m;
    v1.y /= m;
}
