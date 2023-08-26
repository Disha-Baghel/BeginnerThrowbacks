#ifndef PLANET_H
#define PLANET_H

#include "Body.h"
#include <deque>

class Planet: public Body
{
    std::deque<Vec2d> Trace;
    static bool showTrace;
public:
    Planet(float x,float y,float rad,SDL_Color col):Body(x,y,rad,col){Acceleration = Vec2d(0,0.5);}
    void ApplyForce(Vec2d F);
    void Update();
    void Render(SDL_Renderer* renderer);
    static void ShowTrace(bool b){showTrace = b;}
    static bool isShowTrace(){return showTrace;}
};

#endif // PLANET_H
