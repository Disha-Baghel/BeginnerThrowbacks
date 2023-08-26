#include "Triangle.h"
#include <iostream>

void DrawTriangle(SDL_Renderer* renderer,int x1,int y1,int x2,int y2,int x3,int y3)
{
    SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
    SDL_RenderDrawLine(renderer,x2,y2,x3,y3);
    SDL_RenderDrawLine(renderer,x3,y3,x1,y1);
}

float LineEq(float x1,float y1,float x2,float y2,float y)
{
    return (x2 - x1)/(y2 - y1)*(y - y1) + x1;
}

void FillTriangle(SDL_Renderer* renderer,float x1,float y1,float x2,float y2,float x3,float y3)
{
    float _x1,_x2;
    float py[3] = {y1,y2,y3};
    float px[3] = {x1,x2,x3};
    bool swapped = true;

    while(swapped)
    {
        swapped = false;
        for(int i=0;i<3;i++)
        {
            if(i+1 < 3)
            if(py[i] > py[i+1])
            {
                std::swap(py[i],py[i+1]);
                std::swap(px[i],px[i+1]);
                swapped = true;
            }
        }
    }

    float ysmall = py[0],ymid = py[1],ybig = py[2];
    float xsmall = px[0],xmid = px[1],xbig = px[2];

    for(int y=ysmall+1;y<=ybig;y++)
    {
        if(y < ymid)
            _x1 = LineEq(xmid,ymid,xsmall,ysmall,y);
        else
            _x1 = LineEq(xmid,ymid,xbig,ybig,y);

        _x2 = LineEq(xsmall,ysmall,xbig,ybig,y);

        SDL_RenderDrawLine(renderer,_x1,y,_x2,y);
    }
}
