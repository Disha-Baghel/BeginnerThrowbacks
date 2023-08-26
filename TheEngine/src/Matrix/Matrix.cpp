#include "Matrix.h"
#include <cmath>
#include <iostream>

Mat2x2 RotationMatrix(float angle){
    Mat2x2 matrix;
    angle = 3.14/180 * angle;
    matrix.mat[0][0] = cos(angle);
    matrix.mat[0][1] = -sin(angle);
    matrix.mat[1][0] = sin(angle);
    matrix.mat[1][1] = cos(angle);
    return matrix;
}

Vec2d operator-(Vec2d& v1,Vec2d& v2){
    return {v1.x - v2.x,v1.y - v2.y};
}

Vec2d operator*(Vec2d v,Mat2x2 m){
    Vec2d New;
    New.x = v.x * m.mat[0][0] + v.y * m.mat[0][1];
    New.y = v.x * m.mat[1][0] + v.y * m.mat[1][1];
    return New;
}
