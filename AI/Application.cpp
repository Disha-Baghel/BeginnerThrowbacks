#include "Application.h"
#include "image.h"

Game* Game::Game_Instance = new Game();

Game* Game::Instance()
{
    if(Game::Game_Instance == NULL)
        Game::Game_Instance = new Game();

    return Game::Game_Instance;
}

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width,height,0,&window,&renderer);
    running = SDL_TRUE;
    snake = new Snake(renderer,event);
    food = new Food(renderer);
    score = 0;
    Body = Create_Texture("body.png");
    Tail_end = Create_Texture("tail_end.png");
    Tail_turn = Create_Texture("tail_turn.png");
    reached_x = false;
}

Game::~Game()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
#include <iostream>
bool Game::loop()
{
    Event_Handler();
    logic();
    SDL_SetRenderDrawColor(renderer,248,248,248,255);
    SDL_RenderClear(renderer);

    food->show();
    snake->show();

    for(int i=body.size()-1; i>=0; i--)
    {
        int angle = body[i].second;
        SDL_Rect rect = body[i].first;

        if(body[i].second != body[i-1].second  && i != 0)
        {
            if((body[i+1].second == 3 && body[i-1].second == 2) || (body[i+1].second == 0 && body[i-1].second == 1))
                angle = 0;
            else if ((body[i+1].second == 2 && body[i-1].second == 3) || (body[i+1].second == 1 && body[i-1].second == 0))
                angle = 2;
            else if ((body[i+1].second == 1 && body[i-1].second == 2) || (body[i+1].second == 0 && body[i-1].second == 3))
                angle = 1;
            else if ((body[i+1].second == 3 && body[i-1].second == 0) || (body[i+1].second == 2 && body[i-1].second == 1))
                angle = 3;
            SDL_RenderCopyEx(renderer,Tail_turn,NULL,&rect,90*angle,NULL,SDL_FLIP_NONE);
        }
        else
        {
            if(i < body.size()-1)
                SDL_RenderCopyEx(renderer,Body,NULL,&rect,90*(angle%2),NULL,SDL_FLIP_NONE); // direction returns up:2, down:0, left:1,
            else                                                                            // right:3 and initial image is down.
                SDL_RenderCopyEx(renderer,Tail_end,NULL,&rect,90*angle,NULL,SDL_FLIP_NONE);
        }
    }

    SDL_RenderPresent(renderer);

    return running;
}

void Game::logic()
{
    SDL_Rect r1 = snake->get_rect();
    SDL_Rect r2 = food->get_rect();

    if(SDL_HasIntersection(&r1,&r2))
    {
        score++;
        std::pair<SDL_Rect,int> s;
        s.first = snake->get_rect();
        s.second = snake->get_direction();
        body.push_back(s);
        food = new Food(renderer);
    }

    if(body.size()>0)
    {
        body[0].first = snake->get_rect();
        body[0].second = snake->get_direction();

        for(int i=body.size()-1; i>0; i--)
        {
            body[i] = body[i-1];
        }
    }
}

void Game::Event_Handler()
{
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            running = SDL_FALSE;
            break;
        }
    }
}
