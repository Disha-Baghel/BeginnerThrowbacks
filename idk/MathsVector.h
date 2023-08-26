#pragma once

struct Vec2d
{
    float x=0,y=0;
    float mag();
    void normalize();
    void limit(float m);
};

Vec2d operator+(Vec2d v1,Vec2d &v2);
void operator+=(Vec2d &v1,Vec2d &v2);
Vec2d operator-(Vec2d v1,Vec2d &v2);
void operator-=(Vec2d &v1,Vec2d &v2);
Vec2d operator*(Vec2d v1,Vec2d &v2);
void operator*=(Vec2d &v1,Vec2d &v2);
Vec2d operator-(Vec2d v);

Vec2d operator*(Vec2d v1,float m);
void operator*=(Vec2d &v1,float m);
Vec2d operator/(Vec2d v1,float m);
void operator/=(Vec2d &v1,float m);

struct Vec3d
{
    float x=0,y=0,z=0;
};
