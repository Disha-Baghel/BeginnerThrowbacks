#include <iostream>
#include "snake.h"
#include "image.h"

Snake::Snake(SDL_Renderer* renderer,SDL_Event& event,SDL_Rect rect)
{
    this->renderer = renderer;
    this->event = &event;
    if(rect.x == -1)
    {
        x = 400;
        y = 250;
        this->rect = {(int)x,(int)y,20,20};
    }
    else
    {
        x = rect.x;
        y = rect.y;
        this->rect = rect;
    }
    dir = left;
    speed = 20;

    snake_head = Create_Texture("Snake_head.png");
    angle = 0;
}

void Snake::show()
{
    Event_Handler();
    logic();
    SDL_RenderCopyEx(renderer,snake_head,NULL,&rect,90*angle,NULL,SDL_FLIP_NONE);
    SDL_Delay(70);
}

void Snake::Event_Handler()
{
    if(event->type == SDL_KEYDOWN)
    {
        switch(event->key.keysym.sym)
        {
        case SDLK_UP:
            if(dir != down)
                dir = up;
            break;
        case SDLK_DOWN:
            if(dir != up)
                dir = down;
            break;
        case SDLK_LEFT:
            if(dir != right)
                dir = left;
            break;
        case SDLK_RIGHT:
            if(dir != left)
                dir = right;
            break;
        }
    }
}

void Snake::logic()
{
    switch(dir)
    {
    case up:
        y-=speed;
        angle=2;
        break;
    case down:
        y+=speed;
        angle=0;
        break;
    case left:
        x-=speed;
        angle=1;
        break;
    case right:
        x+=speed;
        angle=3;
        break;
    }

    if(x < 0)
        x=800;
    else if(x>800)
        x = 0;
    else if(y < 0)
        y = 500;
    else if(y > 500)
        y = 0;

    rect.x = x;
    rect.y = y;
}

SDL_Rect Snake::get_rect()
{
    return rect;
}

void Snake::set_direction(int d)
{
    switch(d)
    {
        case 0: dir = down;break;
        case 1: dir = left;break;
        case 2: dir = up;break;
        case 3: dir = right;break;
    }
}

int Snake::get_direction()
{
    return dir;
}
