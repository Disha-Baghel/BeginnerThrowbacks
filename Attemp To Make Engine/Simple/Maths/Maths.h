#ifndef MATHS_H_INCLUDED
#define MATHS_H_INCLUDED

#include <cmath>
#include "Vector/Vector.h"
#include "Matrix/Matrix.h"

#define degree

#ifdef radian
#undef degree
#endif // radian

#ifdef degree
#define M_PI			180
#define HALF_PI			90
#define QUARTER_PI		45
#endif // degree

#ifdef radian
#define M_PI			3.14159265358979323846
#define HALF_PI			1.57079632679489661923
#define QUARTER_PI		0.785398163397448309616
#endif // radian

#define M_1_PI			0.318309886183790671538
#define M_2_PI			0.636619772367581343076
#define M_2_SQRT_PI		1.12837916709551257390
#define M_SQRT_2		1.41421356237309504880
#define M_1_SQRT_2		0.707106781186547524401
#define M_E				2.71828182845904523536

inline float invSqrt(float x)
{
	float xhalf = 0.5f * x;
	int i = *(int*)&x;
	i = 0x5f3759df - (i>>1);
	x = *(float*)&i;
	x = x * (1.5f - xhalf*x*x);
	return x;
}

inline const float ToRadians(float deg)
{
	return deg * 0.01745329251; // 0.01745329251 => M_PI/180
}

inline float map(float n,float start1,float stop1,float start2,float stop2)
{
    return ((n-start1)/(stop1-start1))*(stop2-start2)+start2;
}

#endif // MATHS_H_INCLUDED
