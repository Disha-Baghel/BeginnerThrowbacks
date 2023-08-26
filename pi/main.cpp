#include <SDL2/SDL.h>
#include <iostream>

bool prime[10000000] = {false};
int last = 0;

bool IsPrime(int num)
{
    if(num > last)
    {
        for(int i=2;i<num/2;i++)
        {
            if(num%i == 0)
                return false;
        }
        last = num;
        prime[num] = true;
        return true;
    }
    else
        return prime[num];
}

int main(int argc,char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_CreateWindowAndRenderer(800,500,0,&window,&renderer);

    bool running = true;
    SDL_Event event;
    float mag = 0.01;
    float theta = 0;

    while(running)
    {
        if(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT: running = false;break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_UP: mag += 1;break;
                        case SDLK_DOWN: if(mag>1)mag -= 1;break;
                    }
                    break;
                case SDL_MOUSEWHEEL: mag -= event.wheel.y;if(mag <= 0 )mag = 1;
            }
        }

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,255,255,255);

        for(int i=1;i<1000000;i++)
        {
            int x = i*SDL_sin((i+theta))/mag;
            if(x>1000)
                break;
            if(IsPrime(i))
            {
                int y = i*SDL_cos((i+theta))/mag;
                x += 400;
                y += 250;

                SDL_RenderDrawPoint(renderer,x,y);
            }
        }

        SDL_RenderPresent(renderer);
        theta += 0.01;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
