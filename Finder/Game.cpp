#include <iostream>
#include "Game.h"

Game* Game::Game_Instance = NULL;

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
    running = true;
    Block::size = Block_size;
    Block::renderer = renderer;

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
            block[i][j] = new Block(j,i);
    }

    x_pos = 0;
    y_pos = 0;
    block[y_pos][x_pos]->path = true;
    block[rows-1][cols-1]->end = true;
}

void Game::EventHandler()
{
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT: running = false;break;
            case SDL_MOUSEBUTTONDOWN:
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT: int x,y;
                                            SDL_GetMouseState(&x,&y);
                                            block[y/Block_size][x/Block_size]->wall = true;
                }
        }
    }
}

std::vector<Block*> Game::Neighbors(Block* b)
{
    std::vector<Block*> temp;

    int x = b->get_x()/Block_size;
    int y = b->get_y()/Block_size;

    //if(x - 1 >= 0 && y - 1 >= 0)
        //temp.push_back(block[y-1][x-1]);
    if(y-1 >= 0)
        temp.push_back(block[y-1][x]);
    //if(x+1 < cols && y-1 >= 0)
        //temp.push_back(block[y-1][x+1]);
    if(x-1 >= 0)
        temp.push_back(block[y][x-1]);
    if(x+1 < cols)
        temp.push_back(block[y][x+1]);
    //if(x-1 >= 0 && y+1 < rows)
        //temp.push_back(block[y+1][x-1]);
    if(y+1 < rows)
        temp.push_back(block[y+1][x]);
    //if(x+1 < cols && y+1 < rows)
      //  temp.push_back(block[y+1][x+1]);

    return temp;
}

Block* NeighborWithMinF(std::vector<Block*> set)
{
    Block* BlockWithMinF = set[0];
    for(auto s: set)
    {
        if(s->f < BlockWithMinF->f)
            BlockWithMinF = s;
    }

    return BlockWithMinF;
}

void Remove(std::vector<Block*> &set,Block* elem)
{
    for(auto it=set.begin();it!=set.end();it++)
    {
        if(*it == elem)
        {
            set.erase(it);
            break;
        }
    }
}

bool isPresent(std::vector<Block*> set,Block* elem)
{
    for(int i=0;i<set.size();i++)
    {
        if(set[i] == elem)
            return true;
    }
    return false;
}

float Game::CalculateH(Block* elem,Block* dest)
{
    return SDL_max(SDL_abs(elem->get_x() - dest->get_x()),SDL_abs(elem->get_y() - dest->get_y()));
}

bool GreaterF(std::vector<Block*> openSet,Block* elem)
{
    for(auto s: openSet)
    {
        if(s->f < elem->f)
            return true;
    }
    return false;
}

void Game::logic()
{
    std::vector<Block*> openSet,closeSet;
    openSet.push_back(block[0][0]);
    Block* current;

    while(!openSet.empty())
    {
        current = NeighborWithMinF(openSet);
        closeSet.push_back(current);
        Remove(openSet,current);

        if(current == block[rows-1][cols-1])
            break;

        std::vector<Block*> neighbor = Neighbors(current);
        for(int i=0;i<neighbor.size();i++)
        {
            if(isPresent(closeSet,neighbor[i]) || neighbor[i]->wall)
                continue;

            neighbor[i]->g = current->g ;
            neighbor[i]->h = CalculateH(neighbor[i],block[rows-1][cols-1]);
            neighbor[i]->f = neighbor[i]->g + neighbor[i]->h;
            neighbor[i]->parent = current;

            if(isPresent(openSet,neighbor[i]) && GreaterF(openSet,neighbor[i]))
                continue;
            else
                openSet.push_back(neighbor[i]);
        }
    }

    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            block[i][j]->path = false;

    Block* b = closeSet[closeSet.size() - 1];
    while(b != block[0][0])
    {
        b = b->parent;
        b->path = true;
    }
}

void Game::draw()
{
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            block[i][j]->draw();
        }
    }

    SDL_RenderPresent(renderer);
}

void Game::loop()
{
    while(running)
    {
        EventHandler();
        logic();
        draw();
    }
}
