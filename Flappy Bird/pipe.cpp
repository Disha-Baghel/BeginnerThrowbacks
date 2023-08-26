#include <stdlib.h>
#include <time.h>
#include "pipe.h"
#include "ImageLoad.h"

#define height 700
#define width 800

Pipe::Pipe(SDL_Renderer *renderer)
{
    this->renderer = renderer;

    srand(time(NULL));
    int spacing = rand() % 80 + (height/4);
    int centery = rand() % height + 10;
    this->top = centery - spacing/2;
    this->bottom = height - (centery + spacing/2);
    this->x = width;
    this->w = 50;
    this->speed = 3;

    this->highlight = false;

    pipeTexture[0] = loadImage(renderer,"img/pipeTophit.png");
    pipeTexture[1] = loadImage(renderer,"img/pipeBottomhit.png");
    pipeTexture[2] = loadImage(renderer,"img/pipeTop.png");
    pipeTexture[3] = loadImage(renderer,"img/pipeBottom.png");
}

void Pipe::pipeUpdate()
{
    this->x -= this->speed;

    pipe1 = {this->x,0,this->w,this->top};
    pipe2 = {this->x,height - this->bottom,this->w,this->bottom};
}

void Pipe::drawpipe()
{
    SDL_SetRenderDrawColor(renderer,255,255,255,255);

    if(this->highlight)
    {
        SDL_RenderCopy(renderer,pipeTexture[0],nullptr,&pipe1);
        SDL_RenderCopy(renderer,pipeTexture[0],nullptr,&pipe2);
    }
    else
    {
        SDL_RenderCopy(renderer,pipeTexture[2],nullptr,&pipe1);
        SDL_RenderCopy(renderer,pipeTexture[3],nullptr,&pipe2);
    }

    this->highlight = false;
}

bool Pipe::offScreen()
{
    return (this->x < -width);
}

