#include "Body.h"

Vec2D VecAtAngle(float mag,float angle){
    Vec2D v;
    angle = - angle;
    angle = 3.14159256/180 * angle;
    v.x = mag*SDL_cos(angle);
    v.y = mag*SDL_sin(angle);
    return v;
}

Body::Body(int x,int y,int width,int height,SDL_Color col){
    Position = {x,y};
    Velocity = Acceleration = {0,0};
    mass = 1;
    BodyCol = col;
    Width = width;
    Height = height;
}

void Body::ApplyForce(Vec2D F){
    Acceleration += F/mass;
}

void Body::Update(){
    Velocity += Acceleration;
    Position += Velocity;
    if(Position.x > 800 - Width || Position.x < 0 || Position.y < 0 || Position.y > 500 - Height)
        Position -= Velocity;
    Acceleration = {0,0};
}

void Body::Render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer,BodyCol.r,BodyCol.g,BodyCol.b,BodyCol.a);
    SDL_Rect rect = {Position.x,Position.y,Width,Height};
    SDL_RenderDrawRect(renderer,&rect);
}
