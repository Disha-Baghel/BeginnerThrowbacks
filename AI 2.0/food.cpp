#include <stdlib.h>
#include <ctime>
#include "food.h"
#include <iostream>

SDL_Renderer* Food::renderer;
int Food::size;
int Food::prev_x;
int Food::prev_y;

void Food::init(SDL_Renderer* Renderer,int Size)
{
    renderer = Renderer;
    size = Size;
}

Food::Food()
{
    srand(time(NULL));
    int x,y;
    do
    {
        x = (rand() % (800/size))*size;
        y = (rand() % (500/size))*size;
    }while(prev_x == x && prev_y == y);

    prev_x = rect.x = x;
    prev_y = rect.y = y;
    rect.w = size;
    rect.h = size;

    food = Create_Texture("food.png");
}

void Food::draw()
{
    SDL_RenderCopy(renderer,food,NULL,&rect);
}

SDL_Rect& Food::get_rect()
{
    return rect;
}
