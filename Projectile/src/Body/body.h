#ifndef BODY_H
#define BODY_H

#include <SDL2/SDL.h>

struct Vec2D{
    float x,y;
    template <typename type>
    Vec2D operator/(type t){
        return {x/t,y/t};
    }
    void operator+=(Vec2D v){
        x += v.x;
        y += v.y;
    }
    void operator-=(Vec2D v){
        x -= v.x;
        y -= v.y;
    }
};

Vec2D VecAtAngle(float mag,float angle);

class Body{
    int Width,Height;
    float mass;
    Vec2D Position,Velocity,Acceleration;
    SDL_Color BodyCol;
public:
    Body(int x,int y,int width,int height,SDL_Color col);
    void ApplyForce(Vec2D F);
    void SetVelocity(Vec2D V){Velocity = V;}
    void Update();
    void Render(SDL_Renderer* renderer);
};

#endif // BODY_H
