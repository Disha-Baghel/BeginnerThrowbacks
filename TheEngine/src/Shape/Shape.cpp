#include "Shape.h"
#include <iostream>

Shape::Shape(){
    rectMode = NONE;
    Origin={0,0};
    rotateAngle=0;
}

void Shape::Push(){
    ShapeRectMode = rectMode;
    ShapeOrigin = Origin;
    ShapeRotateAngle = rotateAngle;
    rotateAngle = 0;
}

void Shape::Pop(){
    rectMode = ShapeRectMode;
    Origin = ShapeOrigin;
    rotateAngle = ShapeRotateAngle;
}

void Shape::Point(float x,float y,Color col,Blend blendMode){
    SDL_SetRenderDrawBlendMode(renderer,(SDL_BlendMode)blendMode);
    SDL_SetRenderDrawColor(renderer,col.r,col.g,col.b,col.a);
    Vec2d Pos = RotateVec2d({x,y},rotateAngle);
    SDL_RenderDrawPoint(renderer,Origin.x + Pos.x,Origin.y + Pos.y);
}

void Shape::Line(float x1,float y1,float x2,float y2,Color col,Blend blendMode){
    SDL_SetRenderDrawBlendMode(renderer,(SDL_BlendMode)blendMode);
    SDL_SetRenderDrawColor(renderer,col.r,col.g,col.b,col.a);
    Vec2d Pos1 = RotateVec2d({x1,y1},rotateAngle);
    Vec2d Pos2 = RotateVec2d({x2,y2},rotateAngle);
    SDL_RenderDrawLine(renderer,Origin.x + Pos1.x,Origin.y + Pos1.y,Origin.x + Pos2.x,Origin.y + Pos2.y);
}

void Shape::Rect(float x,float y,float w,float h,Color col,Blend blendMode){
    switch(rectMode){
        case NONE:
                        Line(x   , y   , x+w , y   ,col,blendMode);
                        Line(x+w , y   , x+w , y+h ,col,blendMode);
                        Line(x+w , y+h , x   , y+h ,col,blendMode);
                        Line(x   , y+h , x   , y   ,col,blendMode);
                        break;

        case CENTERED:
                        Line(x-w/2 , y-h/2 , x+w/2 , y-h/2 ,col,blendMode);
                        Line(x+w/2 , y-h/2 , x+w/2 , y+h/2 ,col,blendMode);
                        Line(x+w/2 , y+h/2 , x-w/2 , y+h/2 ,col,blendMode);
                        Line(x-w/2 , y+h/2 , x-w/2 , y-h/2 ,col,blendMode);
                        break;
    }
}

float Shape::LineEq(float x1,float y1,float x2,float y2,float y)
{
    return (x2 - x1)/(y2 - y1)*(y - y1) + x1;
}

void Shape::FilledTriangle(Vec2d v1,Vec2d v2,Vec2d v3,Color col,Blend blendMode){
    SDL_SetRenderDrawBlendMode(renderer,(SDL_BlendMode)blendMode);
    SDL_SetRenderDrawColor(renderer,col.r,col.g,col.b,col.a);

    Mat2x2 RotateMatrix = RotationMatrix(rotateAngle);
    v1 = v1 * RotateMatrix;
    v2 = v2 * RotateMatrix;
    v3 = v3 * RotateMatrix;

    float _x1,_x2;
    float py[3] = {Origin.y + v1.y,Origin.y + v2.y,Origin.y + v3.y};
    float px[3] = {Origin.x + v1.x,Origin.x + v2.x,Origin.x + v3.x};
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

    for(int y=ysmall+1;y<ybig;y++)
    {
        if(y < ymid)
            _x1 = LineEq(xmid,ymid,xsmall,ysmall,y);
        else
            _x1 = LineEq(xmid,ymid,xbig,ybig,y);

        _x2 = LineEq(xsmall,ysmall,xbig,ybig,y);

        SDL_RenderDrawLine(renderer,_x1,y,_x2,y);
    }
}

void Shape::FillRect(float x,float y,float w,float h,Color col,Blend blendMode){
    switch(rectMode){
        case NONE:
                        FilledTriangle({x,y},{x+w,y},{x+w,y+h},col,blendMode);
                        FilledTriangle({x,y},{x,y+h},{x+w,y+h},col,blendMode);
                        break;

        case CENTERED:
                        FilledTriangle({x-w/2,y-h/2},{x+w/2,y-h/2},{x+w/2,y+h/2},col,blendMode);
                        FilledTriangle({x-w/2,y-h/2},{x-w/2,y+h/2},{x+w/2,y+h/2},col,blendMode);
                        break;
    }
}

void Shape::Ellipse(float x,float y,float radiusX,float radiusY,Color col,Blend blendMode){

    if(radiusY == -1){
        radiusY = radiusX;
    }

    SDL_SetRenderDrawBlendMode(renderer,(SDL_BlendMode)blendMode);
    SDL_SetRenderDrawColor(renderer,col.r,col.g,col.b,col.a);

    float PrevY = radiusY;
    for(float i=1;i<=radiusX;i++){
        float j = SDL_sqrt(radiusY*radiusY - ((radiusY*radiusY)*i*i/(radiusX*radiusX)));
        SDL_RenderDrawLine(renderer,Origin.x + x-i,Origin.y + y-j,Origin.x + x-(i-1),Origin.y + y-PrevY);
        SDL_RenderDrawLine(renderer,Origin.x + x-i,Origin.y + y+j,Origin.x + x-(i-1),Origin.y + y+PrevY);
        SDL_RenderDrawLine(renderer,Origin.x + x+i,Origin.y + y-j,Origin.x + x+(i-1),Origin.y + y-PrevY);
        SDL_RenderDrawLine(renderer,Origin.x + x+i,Origin.y + y+j,Origin.x + x+(i-1),Origin.y + y+PrevY);
        PrevY = j;
    }
}

void Shape::Ellipse(float x,float y,float radiusX,Color col,Blend blendMode){
    Ellipse(x,y,radiusX,-1,col,blendMode);
}

void Shape::FillEllipse(float x,float y,float radiusX,Color col,Blend blendMode){
    FillEllipse(x,y,radiusX,-1,col,blendMode);
}

void Shape::FillEllipse(float x,float y,float radiusX,float radiusY,Color col,Blend blendMode){

    if(radiusY == -1){
        radiusY = radiusX;
    }

    SDL_SetRenderDrawBlendMode(renderer,(SDL_BlendMode)blendMode);
    SDL_SetRenderDrawColor(renderer,col.r,col.g,col.b,col.a);

    for(int i=0;i<=radiusX;i++){
        float j = SDL_sqrt(radiusY*radiusY - ((radiusY*radiusY)*i*i/(radiusX*radiusX)));
        SDL_RenderDrawLine(renderer,Origin.x + x-i,Origin.y + y-j,Origin.x + x-i,Origin.y + y);
        SDL_RenderDrawLine(renderer,Origin.x + x-i,Origin.y + y+j,Origin.x + x-i,Origin.y + y);
        SDL_RenderDrawLine(renderer,Origin.x + x+i,Origin.y + y-j,Origin.x + x+i,Origin.y + y);
        SDL_RenderDrawLine(renderer,Origin.x + x+i,Origin.y + y+j,Origin.x + x+i,Origin.y + y);
    }
}
