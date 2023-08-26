#ifndef MATRIX_H
#define MATRIX_H

struct Vec2d{
    float x,y;
};

struct Mat2x2{float mat[2][2];};
Mat2x2 RotationMatrix(float angle);

Vec2d operator-(Vec2d& v1,Vec2d& v2);
Vec2d operator*(Vec2d v,Mat2x2 m);

#endif // MATRIX_H
