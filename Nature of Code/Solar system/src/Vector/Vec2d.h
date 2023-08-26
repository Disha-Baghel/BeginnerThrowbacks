#ifndef VEC2D_H
#define VEC2D_H

#include <cmath>

struct Vec2d{
    float x,y;
    Vec2d(float x=0,float y=0){this->x = x;this->y = y;}
    Vec2d operator+(Vec2d v){
        v.x += x;
        v.y += y;
        return v;
    }
    Vec2d operator-(Vec2d v){
        v.x -= x;
        v.y -= y;
        return v;
    }
    void operator+=(Vec2d V){
        *this = *this + V;
    }
    void operator-=(Vec2d V){
        *this = *this - V;
    }
    Vec2d operator*(float d){
        return {x*d,y*d};
    }
    void operator*=(float d){
        *this = *this * d;
    }
    Vec2d operator/(float d){
        return {x/d,y/d};
    }
    float mag(){
        return sqrt(x*x + y*y);
    }
    void normalize(){
        float m = mag();
        x /= m;
        y /= m;
    }
};

#endif // VEC2D_H
