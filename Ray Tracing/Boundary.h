#pragma once

#include <SDL2/SDL.h>
#include "vec2d.h"

struct Boundary
{
    vec2d a,b;
    Boundary(float x1,float y1,float x2,float y2)
    {
        this->a = {x1,y1};
        this->b = {x2,y2};
    }

    void draw(SDL_Renderer* renderer)
    {
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderDrawLine(renderer,a.x,a.y,b.x,b.y);
    }
};
