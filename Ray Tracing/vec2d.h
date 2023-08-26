#pragma once

#include <math.h>

struct vec2d
{
    float x,y;
    void normalize()
    {
        const float den = sqrt(x*x + y*y);
        x /= den;
        y /= den;
    }

    void add(vec2d vel)
    {
        x += vel.x;
        y += vel.y;
    }

    void setMag(float mag)
    {
        float den = sqrt(x*x + y*y);
        x = (x/den) * mag;
        y = (y/den) * mag;
    }

    static vec2d fromAngle(float angle)
    {
        vec2d dir =  {(float)cos(angle),(float)sin(angle)};
        return dir;
    }
};
