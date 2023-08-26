#include <iostream>
#include <SDL2/SDL.h>
#include <time.h>

SDL_Renderer* renderer;

void point(float radius,float angle)
{
    angle = 3.14/180 * angle;
    int x = 400 + (400 + radius)*SDL_sin(angle);
    int y = 250 + (250 + radius)*SDL_cos(angle);
    SDL_RenderDrawPoint(renderer,x,y);
}

void spiral(int _rad)
{
    float ang=0;
    float rad = _rad;
    while(rad<300)
    {
        point(rad,ang);
        ang++;
        rad+=0.1;
    }
}

int main(int argc,char** argv)
{
    SDL_Window* window;
    SDL_CreateWindowAndRenderer(800,500,0,&window,&renderer);
    bool running = true;
    SDL_Event event;
    int _rad = 1;
    int delta = 1;

    while(running)
    {
        //ang++;
        if(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT: running = false;break;
            }
        }

        if(_rad == 300)
            delta *= -1;

        _rad += delta;

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        spiral(_rad);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
