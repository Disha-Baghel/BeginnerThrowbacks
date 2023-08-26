#include "Engine.h"

SDL_Renderer* Engine::renderer;

void Engine::CreateWindow(int width,int height)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width,height,SDL_WINDOW_RESIZABLE,&window,&renderer);
    WIDTH = width;
    HEIGHT = height;
    running = true;
}

void Engine::EventHandler()
{
    SDL_GetWindowSize(window,&WIDTH,&HEIGHT);
    SDL_GetMouseState(&mouseX,&mouseY);

    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT: running = false;break;
            case SDL_KEYDOWN: onKeyClick();break;
            case SDL_MOUSEBUTTONDOWN: onMouseClick();break;
        }
    }
}

void Engine::render()
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    draw();

    SDL_RenderPresent(renderer);
}

void Engine::run()
{
    while(running)
    {
        EventHandler();
        logic();
        render();
    }
}

void Engine::DrawPoint(int x, int y,Paint p,SDL_BlendMode mode)
{
    SDL_SetRenderDrawBlendMode(renderer,mode);
    SDL_SetRenderDrawColor(renderer,p.r,p.g,p.b,p.a);
    SDL_RenderDrawPoint(renderer,x,y);
}
