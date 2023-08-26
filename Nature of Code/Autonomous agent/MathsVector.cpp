#include "MathsVector.h"
#include <cmath>

float Vec2d::magSq()
{
    return x*x + y*y;
}

float Vec2d::mag()
{
    return sqrt(magSq());
}

void Vec2d::setMag(float m)
{
    normalize();
    x *= m;
    y *= m;
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

float Vec2d::heading()
{
    return atan2(y,x);
}

void Vec2d::rotate(float theta)
{
    x = x*cos(theta) - y*sin(theta);
    y = x*sin(theta) + y*cos(theta);
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
