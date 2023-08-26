#include "Block.h"

int Block::size;
SDL_Renderer* Block::renderer;

Block::Block(int x,int y)
{
    rect.x = x*size;
    rect.y = y*size;
    rect.w = size;
    rect.h = size;
    wall = path = end = false;
    f = g = h = 0;
    parent = NULL;
}

void Block::draw()
{
    if(wall)
        SDL_SetRenderDrawColor(renderer,100,100,100,255);
    else if(path)
        SDL_SetRenderDrawColor(renderer,0,255,0,255);
    else if(end)
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
    else
        SDL_SetRenderDrawColor(renderer,100,100,200,255);

    SDL_RenderFillRect(renderer,&rect);

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderDrawRect(renderer,&rect);
}

void Block::set_pos(int x,int y)
{
    rect.x = x*size;
    rect.y = y*size;
}

int Block::get_x()
{
    return rect.x;
}

int Block::get_y()
{
    return rect.y;
}
