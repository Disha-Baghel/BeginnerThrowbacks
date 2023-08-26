#ifndef SHAPE_H
#define SHAPE_H

#include <SDL2/SDL.h>
#include "Matrix.h"

struct Color{
    Uint8 r,g,b,a=255;
};

enum RectMode{NONE,CENTERED};

enum Blend{BLENDMODE_ADD = SDL_BLENDMODE_ADD,
           BLENDMODE_BLEND = SDL_BLENDMODE_BLEND,
           BLENDMODE_INVALID = SDL_BLENDMODE_INVALID,
           BLENDMODE_MOD = SDL_BLENDMODE_MOD,
           BLENDMODE_NONE = SDL_BLENDMODE_NONE};

class Shape{
    RectMode rectMode,ShapeRectMode;
    Vec2d Origin,ShapeOrigin;
    float rotateAngle,ShapeRotateAngle;
    float LineEq(float x1,float y1,float x2,float y2,float y);
protected:
    int MouseX,MouseY;
protected:
    Shape();
    SDL_Renderer* renderer;
    void Translate(int x,int y){Origin.x += x;Origin.y += y;MouseX -= Origin.x;MouseY -= Origin.y;}
    Vec2d RotateVec2d(Vec2d v,float angle){v = v * RotationMatrix(angle);return v;};
    void Rotate(float angle){rotateAngle = angle;}
    void Push();
    void Pop();

    Vec2d GetOrigin(){return Origin;}

    void SetRectMode(RectMode rm){this->rectMode = rm;}

    void Point(float x,float y,Color col={255,255,255,255},Blend blendMode = BLENDMODE_NONE);

    void Line(float x1,float y1,float x2,float y2,Color col={255,255,255,255},Blend blendMode = BLENDMODE_NONE);

    void FilledTriangle(Vec2d v1,Vec2d v2,Vec2d v3,Color col={255,255,255,255},Blend blendMode = BLENDMODE_NONE);

    void Rect(float x,float y,float w,float h,Color col={255,255,255,255},Blend blendMode = BLENDMODE_NONE);
    void FillRect(float x,float y,float w,float h,Color col={255,255,255,255},Blend blendMode = BLENDMODE_NONE);

    void Ellipse(float x,float y,float radiusX,float radiusY,Color col={255,255,255,255},Blend blendMode = BLENDMODE_NONE);
    void Ellipse(float x,float y,float radiusX,Color col={255,255,255,255},Blend blendMode = BLENDMODE_NONE);
    void FillEllipse(float x,float y,float radiusX,float radiusY,Color col={255,255,255,255},Blend blendMode = BLENDMODE_NONE);
    void FillEllipse(float x,float y,float radiusX,Color col={255,255,255,255},Blend blendMode = BLENDMODE_NONE);
};

#endif // SHAPE_H
