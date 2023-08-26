#include "matrix.h"
#include <cmath>

// For multiplying the matrices
vec3d operator*(vec3d &v,const mat4x4 &m)
{
    vec3d temp;
    temp.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
    temp.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
    temp.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];
    float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];

    if(w != 0.0f)
    {
        temp.x /= w; temp.y /= w; temp.z /= w;
    }
    return temp;
}

vec3d operator+(vec3d &v1,const vec3d &v2)
{
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;

    return v1;
}

triangle operator*(triangle &tri,const mat4x4 &m)
{
    tri.p[0] = tri.p[0] * m;
    tri.p[1] = tri.p[1] * m;
    tri.p[2] = tri.p[2] * m;

    return tri;
}

triangle operator+(triangle &tri,const vec3d& v)
{
    tri.p[0] = tri.p[0] + v;
    tri.p[1] = tri.p[1] + v;
    tri.p[2] = tri.p[2] + v;

    return tri;
}

vec3d operator*(vec3d &v1,vec3d &v2)
{
    vec3d temp;
    temp.x = v1.y*v2.z - v1.z*v2.y;
    temp.y = v1.z*v2.x - v1.x*v2.z;
    temp.z = v1.x*v2.y - v1.y*v2.x;
    return temp;
}

vec3d operator-(vec3d &v1,vec3d &v2)
{
    vec3d temp;
    temp.x = v1.x - v2.x;
    temp.y = v1.y - v2.y;
    temp.z = v1.z - v2.z;
    return temp;
}

float mag(vec3d v)
{
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

