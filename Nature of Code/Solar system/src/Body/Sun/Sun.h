#ifndef SUN_H
#define SUN_H

#include "Body.h"
#include "Planet/Planet.h"

class Sun: public Body
{
public:
    Sun(float x,float y,float rad,SDL_Color col):Body(x,y,rad,col){}
    void Attract(Planet* planet);
    void Update();
    void Render(SDL_Renderer* renderer);
};

#endif // SUN_H
