#include "Shape.h"

void Shape::Point(float x,float y,Color col,Blend blendMode){
    SDL_SetRenderDrawBlendMode(renderer,(SDL_BlendMode)blendMode);
    SDL_SetRenderDrawColor(renderer,col.r,col.g,col.b,col.a);
    SDL_RenderDrawPoint(renderer,Origin.x + x,Origin.y + y);
}

void Shape::Line(float x1,float y1,float x2,float y2,Color col,Blend blendMode){
    SDL_SetRenderDrawBlendMode(renderer,(SDL_BlendMode)blendMode);
    SDL_SetRenderDrawColor(renderer,col.r,col.g,col.b,col.a);
    SDL_RenderDrawLine(renderer,Origin.x + x1,Origin.y + y1,Origin.x + x2,Origin.y + y2);
}

void Shape::Rect(float x,float y,float w,float h,Color col,Blend blendMode){
    SDL_SetRenderDrawBlendMode(renderer,(SDL_BlendMode)blendMode);
    SDL_SetRenderDrawColor(renderer,col.r,col.g,col.b,col.a);

    SDL_Rect rect = {Origin.x + x,Origin.y + y,w,h};

    switch(rectMode){
        case NONE:
                        SDL_RenderDrawRect(renderer,&rect);
                        break;

        case CENTERED:
                        SDL_RenderDrawLine(renderer,Origin.x + x-w/2,Origin.y + y-h/2,x+w/2,y-h/2);
                        SDL_RenderDrawLine(renderer,Origin.x + x+w/2,Origin.y + y-h/2,x+w/2,y+h/2);
                        SDL_RenderDrawLine(renderer,Origin.x + x+w/2,Origin.y + y+h/2,x-w/2,y+h/2);
                        SDL_RenderDrawLine(renderer,Origin.x + x-w/2,Origin.y + y+h/2,x-w/2,y-h/2);
                        break;
    }
}

void Shape::FillRect(float x,float y,float w,float h,Color col,Blend blendMode){
    SDL_SetRenderDrawBlendMode(renderer,(SDL_BlendMode)blendMode);
    SDL_SetRenderDrawColor(renderer,col.r,col.g,col.b,col.a);

    SDL_Rect rect = {Origin.x + x,Origin.y + y,w,h};

    switch(rectMode){
        case NONE:
                        SDL_RenderFillRect(renderer,&rect);
                        break;

        case CENTERED:
                        rect = {Origin.x + x-w/2,Origin.y + y-h/2,w/2,h/2};
                        SDL_RenderFillRect(renderer,&rect);
                        rect = {Origin.x + x,Origin.y + y-h/2,w/2,h/2};
                        SDL_RenderFillRect(renderer,&rect);
                        rect = {Origin.x + x-w/2,Origin.y + y,w/2,h/2};
                        SDL_RenderFillRect(renderer,&rect);
                        rect = {Origin.x + x,Origin.y + y,w/2,h/2};
                        SDL_RenderFillRect(renderer,&rect);
                        break;
    }
}

void Shape::Ellipse(float x,float y,int radiusX,int radiusY,Color col,Blend blendMode){

    if(radiusY == -1){
        radiusY = radiusX;
    }

    SDL_SetRenderDrawBlendMode(renderer,(SDL_BlendMode)blendMode);
    SDL_SetRenderDrawColor(renderer,col.r,col.g,col.b,col.a);

    float PrevY = radiusY;
    for(int i=1;i<=radiusX;i++){
        float j = SDL_sqrt(radiusY*radiusY - ((radiusY*radiusY)*i*i/(radiusX*radiusX)));
        SDL_RenderDrawLine(renderer,Origin.x + x-i,Origin.y + y-j,Origin.x + x-(i-1),Origin.y + y-PrevY);
        SDL_RenderDrawLine(renderer,Origin.x + x-i,Origin.y + y+j,Origin.x + x-(i-1),Origin.y + y+PrevY);
        SDL_RenderDrawLine(renderer,Origin.x + x+i,Origin.y + y-j,Origin.x + x+(i-1),Origin.y + y-PrevY);
        SDL_RenderDrawLine(renderer,Origin.x + x+i,Origin.y + y+j,Origin.x + x+(i-1),Origin.y + y+PrevY);
        PrevY = j;
    }
}

void Shape::Ellipse(float x,float y,int radiusX,Color col,Blend blendMode){
    Ellipse(x,y,radiusX,-1,col,blendMode);
}

void Shape::FillEllipse(float x,float y,int radiusX,Color col,Blend blendMode){
    FillEllipse(x,y,radiusX,-1,col,blendMode);
}

void Shape::FillEllipse(float x,float y,int radiusX,int radiusY,Color col,Blend blendMode){

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
