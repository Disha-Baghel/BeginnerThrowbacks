#include "snake.h"
#include <iostream>

Snake::Snake(SDL_Renderer* renderer,int size)
{
    this->renderer = renderer;
    this->size = size;
    SDL_Rect head = {400,260,size,size};
    this->step = 0;

    body.push_back(head);
}

void Snake::Eat()
{
    SDL_Rect rect = {(int)x_pos,(int)y_pos,size,size};
    body.push_back(rect);
}

void Snake::logic()
{
    x_pos = Path[step].x;
    y_pos = Path[step].y;
    
    std::vector<SDL_Rect> temp;
    
    SDL_Rect rect = {x_pos,y_pos,size,size};
    temp.push_back(rect);
    for(int i=0;i<body.size()-1;i++)
        temp.push_back(body[i]);
    body = temp;

    step++;
    if(step==Path.size())
        step = 0;
}

void Snake::draw()
{
    SDL_SetRenderDrawColor(renderer,0,255,0,255);
    for(auto b: body)
    {
        SDL_RenderFillRect(renderer,&b);
    }
}

SDL_Rect Snake::get_head()
{
    return body[0];
}

void Snake::getPath(std::vector<SDL_Rect> Path)
{
    this->Path = Path;
}

std::vector<SDL_Rect> Snake::getBody()
{
    return body;
}
