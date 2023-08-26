#ifndef SHAPE_H
#define SHAPE_H

#include <SDL2/SDL.h>

struct Color{
    Uint8 r,g,b,a=255;
};

enum RectMode{NONE,CENTERED};

enum Blend{BLENDMODE_ADD = SDL_BLENDMODE_ADD,
           BLENDMODE_BLEND = SDL_BLENDMODE_BLEND,
           BLENDMODE_INVALID = SDL_BLENDMODE_INVALID,
           BLENDMODE_MOD = SDL_BLENDMODE_MOD,
           BLENDMODE_NONE = SDL_BLENDMODE_NONE};

struct Vec2d{
    float x,y;
};

class Shape
{
    RectMode rectMode;
    Vec2d Origin;
protected:
    Shape(){rectMode = NONE;}
    SDL_Renderer* renderer;
    void translate(float x,float y){Origin.x = x;Origin.y = y;}
    void SetRectMode(RectMode rm){this->rectMode = rm;}
    void Point(float x,float y,Color col={255,255,255,255},Blend blendMode = BLENDMODE_NONE);
    void Line(float x1,float y1,float x2,float y2,Color col={255,255,255,255},Blend blendMode = BLENDMODE_NONE);
    void Rect(float x,float y,float w,float h,Color col={255,255,255,255},Blend blendMode = BLENDMODE_NONE);
    void FillRect(float x,float y,float w,float h,Color col={255,255,255,255},Blend blendMode = BLENDMODE_NONE);
    void Ellipse(float x,float y,int radiusX,int radiusY,Color col={255,255,255,255},Blend blendMode = BLENDMODE_NONE);
    void Ellipse(float x,float y,int radiusX,Color col={255,255,255,255},Blend blendMode = BLENDMODE_NONE);
    void FillEllipse(float x,float y,int radiusX,int radiusY,Color col={255,255,255,255},Blend blendMode = BLENDMODE_NONE);
    void FillEllipse(float x,float y,int radiusX,Color col={255,255,255,255},Blend blendMode = BLENDMODE_NONE);
};

#endif // SHAPE_H
