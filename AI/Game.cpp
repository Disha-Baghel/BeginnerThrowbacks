#include "Game.h"
#include <algorithm>
#include "Path_Finder.h"

Game* Game::Game_Instance = NULL;

Game* Game::Instance()
{
    if(Game::Game_Instance == NULL)
        Game::Game_Instance = new Game();
    return Game_Instance;
}

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width,height,0,&window,&renderer);
    running = true;
    Food::init(renderer,20);
    food = new Food();
    snake = new Snake(renderer,20);

    snake->getPath(FindPath(snake->get_head(),food->get_rect(),snake->getBody()));
}

void Game::EventHandler()
{
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        }
    }
}

void Game::logic()
{
    if(SDL_GetTicks()%30 == 0)
        snake->logic();

    SDL_Rect r1 = snake->get_head();
    SDL_Rect r2 = food->get_rect();
    if(SDL_HasIntersection(&r1,&r2))
    {
        snake->Eat();

        bool yes;
        auto body = snake->getBody();
        do
        {
            yes = false;
            delete food;
            food = new Food();
            SDL_Rect rect = food->get_rect();
            for(auto b: body)
                if(b.x == rect.x && b.y == rect.y)
                    yes = true;
        }
        while(yes);

        snake->getPath(FindPath(snake->get_head(),food->get_rect(),body));
    }
}

void Game::draw()
{
    SDL_SetRenderDrawColor(renderer,248,248,248,255);
    SDL_RenderClear(renderer);

    snake->draw();
    food->draw();

    SDL_RenderPresent(renderer);
}

void Game::Start()
{
    while(running)
    {
        EventHandler();
        logic();
        draw();
    }
}
