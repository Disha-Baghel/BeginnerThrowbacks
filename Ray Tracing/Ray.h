#include <SDL2/SDL.h>
#include "Boundary.h"
#include "vec2d.h"
#include <iostream>

class Ray
{
    vec2d *pos,dir;
    float heading;
public:
    void setHeading(float heading)
    {
        this->heading = heading;
    }

    float Heading()
    {
        return heading;
    }

    Ray(vec2d *pos,float angle)
    {
        this->pos = pos;
        this->dir = vec2d::fromAngle(angle);
    }

    void setAngle(float angle)
    {
        this->dir = vec2d::fromAngle(angle);
    }

    void lookAt(int x,int y)
    {
        this->dir.x = x - this->pos->x;
        this->dir.y = y - this->pos->y;
        this->dir.normalize();
    }

    void draw(SDL_Renderer* renderer)
    {
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderDrawLine(renderer,pos->x,pos->y,dir.x*10 + pos->x,dir.y*10 + pos->y); //Drawing and translating
    }

    vec2d cast(Boundary* wall)
    {
        const float x1 = wall->a.x;
        const float y1 = wall->a.y;
        const float x2 = wall->b.x;
        const float y2 = wall->b.y;

        const float x3 = pos->x;
        const float y3 = pos->y;
        const float x4 = dir.x + pos->x;
        const float y4 = dir.y + pos->y;

        const float den = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
        if(den == 0)
            return {pos->x,pos->y};

        const float t = ((x1 - x3)*(y3 - y4) - (y1 - y3)*(x3 - x4))/den;
        const float u = -((x1 - x2)*(y1 - y3) - (y1 - y2)*(x1 - x3))/den;

        if(t > 0 && t < 1 && u > 0)
        {
            vec2d pt;
            pt.x = x1 + t*(x2 - x1);
            pt.y = y1 + t*(y2 - y1);
            return pt;
        }
        else
            return {pos->x,pos->y};
    }
};
