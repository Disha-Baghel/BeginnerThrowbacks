#ifndef MATH_H
#define MATH_H

#define _USE_MATH_DEFINES
#include <cmath>

constexpr inline float map(float n,float start1,float stop1,float start2,float stop2)
{
    return ((n-start1)/(stop1-start1))*(stop2-start2)+start2;
}

#endif // MATH_H
