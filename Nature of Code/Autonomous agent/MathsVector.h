#pragma once

struct Vec2d
{
    float x=0,y=0;
    float magSq();
    float mag();
    void setMag(float m);
    void normalize();
    void limit(float m);
    float heading();
    void rotate(float theta);
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
