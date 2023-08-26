#include "Planet.h"

bool Planet::showTrace = false;

void Planet::ApplyForce(Vec2d F){
    Acceleration += F/Mass;
}

void Planet::Update(){

    if(showTrace){
        if(Trace.empty()){
            Trace.push_back(Position);
        }
        float distance = (Position - Trace[Trace.size() - 1]).mag();
        if(distance > 3){
            Trace.push_back(Position);
        }
        if(Trace.size() > 50){
            Trace.pop_front();
        }
    }
    else if(Trace.size() > 0){
        Trace.clear();
    }

    Velocity += Acceleration;
    Position += Velocity;
    Acceleration *= 0;
}

void Planet::Render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer,Col.r,Col.g,Col.b,Col.a);
    DrawCircle(renderer,Position,Radius);

    if(showTrace){
        for(int i=0;i<Trace.size()-1;i++){
            SDL_SetRenderDrawColor(renderer,Col.r,Col.g,Col.b,5*i);
            SDL_RenderDrawLine(renderer,Trace[i].x,Trace[i].y,Trace[i+1].x,Trace[i+1].y);
            //SDL_RenderDrawPoint(renderer,T.x,T.y);
        }
    }
}
