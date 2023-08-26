#include "Sun.h"

float constraint(float d,float min,float max){
    d = (d<min)?min:d;
    d = (d>max)?max:d;
    return d;
}

void Sun::Attract(Planet* planet){
    Vec2d Pos = planet->GetPosition();
    Vec2d Force = Pos - Position;
    float distance = Force.mag();
    distance = constraint(distance,5,25);
    Force.normalize();
    float strength = (Mass*planet->GetMass())/(distance*distance);
    Force *= strength;

    planet->ApplyForce(Force);
}

void Sun::Update(){

}

void Sun::Render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer,Col.r,Col.g,Col.b,Col.a);
    DrawCircle(renderer,Position,Radius);
}
