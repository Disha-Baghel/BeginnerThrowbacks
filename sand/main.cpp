#include <iostream>
#include <SDL2/SDL.h>
#include <queue>

class Sand
{
    int x,y;
    float velocity,gravity;
public:
    Sand(int x,int y)
    {
        this->x = x;
        this->y = y;
        this->velocity = 0.01;
        this->gravity = 0.1;
    }
    void draw(SDL_Renderer* renderer)
    {
        logic();
        SDL_RenderDrawPoint(renderer,x,y);
    }
    void logic()
    {
        if(y >= 498)
            velocity *= -1;
        y+=velocity;
        velocity += gravity;
    }
};

int main(int argc,char** destination)
{
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_CreateWindowAndRenderer(800,500,0,&window,&renderer);
    bool running = true;
    SDL_Event event;
    std::queue<Sand*> sand;

    while(running)
    {
        int x,y;
        if(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT: running = false;break;
            }
        }

        SDL_GetMouseState(&x,&y);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        sand.push(new Sand(x,y));

        SDL_Delay(10);

        for(int i=0;i<sand.size();i++)
        {
            sand.front()->draw(renderer);
            Sand* temp = sand.front();
            sand.pop();
            sand.push(temp);
        }

        if(sand.size() > 2000)
            sand.pop();

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
