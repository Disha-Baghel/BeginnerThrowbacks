#include "Game.h"
#include <iostream>

Game* Game::GameInstance = NULL;

Game* Game::Instance()
{
    if(Game::GameInstance == NULL)
        Game::GameInstance = new Game();
    return Game::GameInstance;
}

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width,height,0,&window,&renderer);
    SDL_SetWindowTitle(window,"Ray Tracing");
    running = true;

    particle = new Particle();

    walls.push_back(new Boundary(0,0,SceneW,0));
    walls.push_back(new Boundary(SceneW,0,SceneW,height));
    walls.push_back(new Boundary(0,height,SceneW,height));
    walls.push_back(new Boundary(0,0,0,height));
    walls.push_back(new Boundary(100,0,100,150));
    walls.push_back(new Boundary(100,350,100,500));
    walls.push_back(new Boundary(0,150,100,150));
    walls.push_back(new Boundary(0,350,100,350));

    walls.push_back(new Boundary(300,0,300,150));
    walls.push_back(new Boundary(300,350,300,500));
    walls.push_back(new Boundary(300,150,400,150));
    walls.push_back(new Boundary(300,350,400,350));
}

void Game::EventHandler()
{
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT: running = false;break;
            case SDL_MOUSEMOTION:
                                int x,y;
                                SDL_GetMouseState(&x,&y);
                                particle->update(x,y);
                                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_a:
                    case SDLK_LEFT: particle->rotate(-0.1);break;
                    case SDLK_d:
                    case SDLK_RIGHT: particle->rotate(0.1);break;
                    case SDLK_w: particle->move(5);break;
                    case SDLK_s: particle->move(-5);break;
                }
        }
    }
}

void Game::logic()
{

}

float map(float n,float start1,float stop1,float start2,float stop2) {
  return ((n-start1)/(stop1-start1))*(stop2-start2)+start2;
}

void DrawRect(SDL_Renderer* renderer,int x,int y,int w,int h)
{
    h = (h<0)?0:h;
    SDL_Rect rect = {x,y,w,h};
    rect.w = -w/2;
    rect.h = -h/2;
    SDL_RenderFillRect(renderer,&rect);

    rect.w = -w/2;
    rect.h = h/2;
    SDL_RenderFillRect(renderer,&rect);

    rect.w = w/2;
    rect.h = -h/2;
    SDL_RenderFillRect(renderer,&rect);

    rect.w = w/2;
    rect.h = h/2;
    SDL_RenderFillRect(renderer,&rect);
}

void Game::draw()
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    for(auto wall:walls)
    {
        wall->draw(renderer);
    }

    std::vector<float> scene = particle->look(renderer,walls);

    const float w = SceneW/scene.size();

    for(unsigned int i=0;i<scene.size();i++)
    {
        const float sq = scene[i] * scene[i];
        const float sqw = SceneW*SceneW;
        const float b = map(sq,0,sqw,255,0);
        const float h = map(scene[i],0,SceneW,height,0);

        SDL_SetRenderDrawColor(renderer,255,255,255,b);
        DrawRect(renderer,SceneW + i*w,height/2,w+1,h);
    }

    SDL_RenderPresent(renderer);
}

void Game::start()
{
    while(running)
    {
        EventHandler();
        logic();
        draw();
    }
}
