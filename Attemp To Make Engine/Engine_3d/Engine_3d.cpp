#include <iostream>
#include "Engine_3d.h"

Engine_3d::Engine_3d(int width,int height)
{
    this->width = width;
    this->height = height;
    SDL_CreateWindowAndRenderer(width,height,0,&window,&renderer);
    this->running = true;

    //Projection Matrix
    float fNear = 0.1f;
    float fFar = 1000.0f;
    float fFov = 135.0f;
    float fAspectRatio = (float)height/(float)width;
    float fFovRad =1.0f/SDL_tan(fFov*0.5f / 180.0f * 3.14159f);

    matProj.m[0][0] = fAspectRatio * fFovRad;
    matProj.m[1][1] = fFovRad;
    matProj.m[2][2] = fFar / (fFar - fNear);
    matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
    matProj.m[2][3] = 1.0f;
    matProj.m[3][3] = 0.0f;

    object::renderer = renderer;
    object::width = width;
    object::height = height;
    object::matProj = matProj;
    object::vCamera = {0,0,0};
}

Engine_3d::~Engine_3d()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Engine_3d::EventHandler()
{
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT: this->running = false;break;
        }
    }
}

void Engine_3d::update(void (*DrawCallBack)())
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    DrawCallBack();

    SDL_RenderPresent(renderer);
}

void Engine_3d::Start(void (*DrawCallBack)(void))
{
    while(running)
    {
        EventHandler();
        update(DrawCallBack);
    }
}
