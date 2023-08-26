#include <math.h>
#include "bird.h"
#include "ImageLoad.h"

bird::bird(SDL_Renderer *ren,int size)
{
    this->x = 100;
    this->y = height/2;
    this->size = size;

    this->renderer = ren;

    this->velocity = 0;

    bird1 = loadImage(renderer,"img/bird1.png");
    bird2 = loadImage(renderer,"img/bird2.png");
    bird3 = loadImage(renderer,"img/bird3.png");
}

void bird::drawbird()
{
    this->birdRect = {x,y,size,size};
    SDL_SetRenderDrawColor(this->renderer,255,255,255,255);

    int frequency = 1000/15;
    int time = (SDL_GetTicks()/frequency) % 3;

    switch(time)
    {
        case 0:SDL_RenderCopy(renderer,bird1,nullptr,&birdRect);break;
        case 1:SDL_RenderCopy(renderer,bird2,nullptr,&birdRect);break;
        case 2:SDL_RenderCopy(renderer,bird3,nullptr,&birdRect);break;
    }
}

void bird::gravity()
{
    this->velocity += grav;
    this->velocity *= 0.9;
    this->y += this->velocity;

    if(this->y + this->size > height)
    {
        this->y = height - this->size;
        this->velocity = 0;
    }

    if(this->y - this->size < 0)
    {
        this->y = this->size;
    }
}

void bird::lift()
{
    this->velocity += up;
}
