#include <SDL2/SDL.h>

int branch_count = 3;

class Tree
{
    int x1,y1;
    static SDL_Renderer* renderer;
    Tree* branch;
public:
    static void set_renderer(SDL_Renderer* _renderer)
    {
        renderer = _renderer;
    }
    Tree(int x,int y,int height,float angle = 90);
};

SDL_Renderer* Tree::renderer;

Tree::Tree(int x,int y,int height,float angle)
{
    float ang = 3.14/180 * angle;
    x1 = x + height*SDL_cos(ang);
    y1 = y - height*SDL_sin(ang);

    if(height<20)
        SDL_SetRenderDrawColor(renderer,0,200,0,255);
    else
        SDL_SetRenderDrawColor(renderer,128,64,0,255);

    SDL_RenderDrawLine(renderer,x,y,x1,y1);

    if(height>10)
    {
        float min_angle = 90/(branch_count-1);
        for(int i=0;i<branch_count;i++)
            branch = new Tree(x1,y1,height/1.5,angle/2 + min_angle*i);
    }
}

int main(int argc,char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_CreateWindowAndRenderer(800,500,0,&window,&renderer);
    bool running = true;
    SDL_Event event;
    Tree::set_renderer(renderer);

    int height = 10;

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
                        case SDLK_UP: height++;break;
                        case SDLK_DOWN: if(height>10) height--;break;
                        case SDLK_LEFT: if(branch_count>2) branch_count--;break;
                        case SDLK_RIGHT: if(branch_count<4) branch_count++;break;
                    }
            }
        }

        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderClear(renderer);

        Tree T1(400,480,height);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
