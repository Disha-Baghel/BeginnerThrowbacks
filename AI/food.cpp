#include <stdlib.h>
#include <time.h>
#include "food.h"
#include "image.h"
#include <iostream>

SDL_Texture* Food::food;

Food::Food(SDL_Renderer* renderer)
{
    srand(time(NULL));
    this->renderer = renderer;
    int x = rand() % rand() % 760 + 20;
    int y = rand() % rand() % 460 + 20;

    rect = {x,y,25,25};

    if(Food::food == NULL)
    {
        Food::food = Create_Texture("food.png");
    }
}

void Food::show()
{
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderCopy(renderer,food,NULL,&rect);
}

SDL_Rect Food::get_rect()
{
    return rect;
}
