#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2d {
  public:

    float X,Y;

    Vector2d(float x=0,float y=0): X(x),Y(y) {}

    //addition +
    inline Vector2d operator+(Vector2d v) const {
        return Vector2d(X + v.X,Y + v.Y);
    }

    //subtraction -
    inline Vector2d operator-(Vector2d v) const {
        return Vector2d(X - v.X,Y - v.Y);
    }

    //multiplication
    inline Vector2d operator*(float scalar) const {
        return Vector2d(X*scalar,Y*scalar);
    }

    void Log(std::string msg = "") {
        std::cout<<msg<<"(X Y) = { "<<X<<' '<<Y<<" }"<<std::endl;
    }
};

#endif // VECTOR2D_H
