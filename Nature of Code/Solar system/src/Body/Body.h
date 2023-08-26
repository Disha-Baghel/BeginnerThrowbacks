#ifndef BODY_H
#define BODY_H

#include <SDL2/SDL.h>
#include "Vec2d.h"

class Body{
protected:
    Vec2d Position,Velocity,Acceleration;
    SDL_Color Col;
    float Mass,Radius;
public:
    Body(float x,float y,float rad,SDL_Color col){
            Position = Vec2d(x,y);
        Col = col;
        Mass = 1;
        Radius = rad;
    }
    Vec2d GetPosition(){return Position;}
    void SetAcceleration(Vec2d a){Acceleration = a;}
    void SetVelocity(Vec2d v){Velocity = v;}
    void SetMass(float mass){Mass = mass;}
    float GetMass(){return Mass;}
    virtual void Update() = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;

    void DrawCircle(SDL_Renderer* renderer,Vec2d point,float radius)
    {
        float x1 = radius + point.x;
        float y1 = point.y;
        for(float rad=0.1;rad<=2.01*M_PI;rad+=0.1)
        {
            float x2 = SDL_cos(rad)*radius + point.x;
            float y2 = SDL_sin(rad)*radius + point.y;
            SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
            x1 = x2;
            y1 = y2;
        }
    }
};

#endif // BODY_H
