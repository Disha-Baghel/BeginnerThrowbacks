#include "turtle.h"

#define PI 3.14159265358979323846264338327950288

turtle::turtle(int w,int h)
{
    init_window(w,h);
}

turtle::turtle()
{
    init_window(800,500);
}

void turtle::init_window(int w,int h)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    SDL_CreateWindowAndRenderer(w,h,0,&window,&renderer);

    background(black);
    pencolour(white);

    SDL_RenderPresent(renderer);

    x = w/2;
    y = h/2;
}

turtle::~turtle()
{
    SDL_Event event;

    while(1)
        if(SDL_PollEvent(&event) && event.type == SDL_QUIT)
            SDL_Quit();
}

void turtle::forward(float dist,float angle)
{
    forward_for_circle(dist,angle);
    SDL_RenderPresent(renderer);
    SDL_Delay(Speed);
}

void turtle::forward_for_circle(float dist,float angle)
{
    angle = angle * PI/180;

    float a = dist * SDL_sin(angle);
    float b = dist * SDL_cos(angle);

    SDL_RenderDrawLine(renderer,x,y,x + a,y + b);

    x = x + a;
    y = y + b;
}

void turtle::backward(float dist,float angle)
{
    angle = angle * PI/180;

    float a = dist * SDL_sin(angle);
    float b = dist * SDL_cos(angle);

    SDL_RenderDrawLine(renderer,x,y,x - a,y - b);

    x = x - a;
    y = y - b;

    SDL_RenderPresent(renderer);

    SDL_Delay(Speed);
}

void turtle::speed(int Speed)
{
    this->Speed = Speed;
}

COLOUR turtle::set_colour(int col)
{
    Uint8 r,g,b;
    switch(col)
    {
    case red:
        r = 255;
        g = b = 0;
        break;
    case green:
        r = b = 0;
        g = 255;
        break;
    case blue:
        r = g = 0;
        b = 255;
        break;
    case yellow:
        r = 255;
        g = 255;
        b = 0;
        break;
    case black:
        r = g = b = 0;
        break;
    case white:
        r = g = b = 255;
        break;
    }

    COLOUR ret = {r,g,b};
    return ret;
}

void turtle::background(int col)
{
    bgcolour = set_colour(col);
    clear();
}

void turtle::pencolour(int col)
{
    pen_colour = set_colour(col);
    clear();
}

void turtle::clear()
{
    SDL_SetRenderDrawColor(renderer,bgcolour.r,bgcolour.g,bgcolour.b,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,pen_colour.r,pen_colour.g,pen_colour.b,255);
}

void turtle::pos(int x,int y)
{
    this->x = x;
    this->y = y;
}

void turtle::reset()
{
    background(black);
    pencolour(white);

    x = 400;
    y = 250;
}

void turtle::circle(int radius)
{
    /**************************************************************************************************************\
    ***    Since, forward() takes small_length to complete a full circumference, therefore we need to find it    ***
    ***    circumference = small_length*360                                                                      ***
    ***    2*pi*radius = circumference                                                                           ***
    ***    2*pi*radius = small_length*360                                                                        ***
    ***    2*pi*radius/360 = small_length                                                                        ***
    ***    radius * pi/180 = small_length                                                                        ***
    \***************************************************************************************************************/

    float small_length = radius * PI/180;

    for(int i=0;i<360;++i)
        forward_for_circle(small_length,i);

    SDL_RenderPresent(renderer);
}
