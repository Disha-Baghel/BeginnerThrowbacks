#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

Game* Game::Game_instance;

Game* Game::Instance()
{
    if(Game::Game_instance == NULL)
        Game::Game_instance = new Game();
    return Game::Game_instance;
}

Game::Game()
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(800,500,0,&window,&renderer);
    this->running = true;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
            arr[i][j] = 0;
    }
    set_random_pos();
    changed = false;
}

void Game::set_random_pos()
{
    bool done = false;
    int x,y;
    do
    {
        x = rand() % 4;
        y = rand() % 4;

        if(arr[x][y] == 0)
        {
            arr[x][y] = 2*(rand()%2 + 1);
            done = true;
        }
    }while(!done);
}

void Game::EventHandler()
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT: this->running = false;break;
            case SDL_KEYDOWN:
                if(changed)
                {
                    changed = false;
                    set_random_pos();
                }
                switch(event.key.keysym.sym)
                {
                    case SDLK_DOWN : dir = down;break;
                    case SDLK_LEFT : dir = left;break;
                    case SDLK_UP   : dir = up;break;
                    case SDLK_RIGHT: dir = right;break;
                }
        }
    }
}

void Game::logic()
{
    switch(dir)
    {
        case down: for(int i=0;i<3;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(arr[i][j] == arr[i+1][j] || arr[i+1][j] == 0)
                            {
                                arr[i+1][j] += arr[i][j];
                                arr[i][j] = 0;
                                changed = true;
                            }
                        }
                    }
                    break;
        case left: for(int i=1;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(arr[j][i] == arr[j][i-1] || arr[j][i-1] == 0)
                            {
                                arr[j][i-1] += arr[j][i];
                                arr[j][i] = 0;
                                changed = true;
                            }
                        }
                    }
                    break;
        case up: for(int i=1;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(arr[i][j] == arr[i-1][j] || arr[i-1][j] == 0)
                            {
                                arr[i-1][j] += arr[i][j];
                                arr[i][j] = 0;
                                changed = true;
                            }
                        }
                    }
                    break;
        case right: for(int i=2;i>=0;i--)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(arr[j][i+1] == arr[j][i] || arr[j][i+1] == 0)
                            {
                                arr[j][i+1] += arr[j][i];
                                arr[j][i] = 0;
                                changed = true;
                            }
                        }
                    }
                    break;
    }
}

void Game::set_color(int col)
{
    switch(col)
    {
        case 0   : SDL_SetRenderDrawColor(renderer,100,100,100,255);break;
        case 2   : SDL_SetRenderDrawColor(renderer,255,0,0,255);break;
        case 4   : SDL_SetRenderDrawColor(renderer,0,255,0,255);break;
        case 8   : SDL_SetRenderDrawColor(renderer,0,0,255,255);break;
        case 16  : SDL_SetRenderDrawColor(renderer,255,255,0,255);break;
        case 32  : SDL_SetRenderDrawColor(renderer,255,0,255,255);break;
        case 64  : SDL_SetRenderDrawColor(renderer,0,255,255,255);break;
        case 128 : SDL_SetRenderDrawColor(renderer,200,200,200,255);break;
        case 256 : SDL_SetRenderDrawColor(renderer,100,200,100,255);break;
        case 512 : SDL_SetRenderDrawColor(renderer,100,100,200,255);break;
        case 1024: SDL_SetRenderDrawColor(renderer,200,100,100,255);break;
        case 2048: SDL_SetRenderDrawColor(renderer,100,200,200,255);break;
        case 4096: SDL_SetRenderDrawColor(renderer,200,200,100,255);break;
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            set_color(arr[i][j]);
            SDL_Rect rect = {j*50 + 300,i*50 + 150,50,50};
            SDL_RenderFillRect(renderer,&rect);
        }
    }

    SDL_SetRenderDrawColor(renderer,255,255,255,255);

    for(int i=1;i<4;i++)
    {
        SDL_RenderDrawLine(renderer,i*50 + 300,150,i*50 + 300,350);
        SDL_RenderDrawLine(renderer,300,i*50 + 150,500,i*50 + 150);
    }

    SDL_RenderPresent(renderer);
}

bool Game::loop()
{
    EventHandler();
    logic();
    render();
    return running;
}
