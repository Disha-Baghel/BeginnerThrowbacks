#include "Engine.h"

SDL_Renderer* Engine::renderer;
RectMode Engine::rectMode;
Paint Engine::backgroundColor;

void Engine::CreateWindow(int width,int height)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width,height,SDL_WINDOW_RESIZABLE,&window,&renderer);
    WIDTH = width;
    HEIGHT = height;
    running = true;
    rectMode = NONE;
    Image::renderer = &*renderer;
}

void Engine::EventHandler()
{
    SDL_GetWindowSize(window,&WIDTH,&HEIGHT);
    SDL_GetMouseState(&mouseX,&mouseY);

    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT: running = false;break;
            case SDL_KEYDOWN: onKeyClick();break;
            case SDL_MOUSEBUTTONDOWN: onMouseClick();break;
        }
    }
}

void Engine::setRectMode(RectMode rm)
{
    rectMode = rm;
}

void Engine::Drawline(int x1,int y1,int x2,int y2,Paint p,SDL_BlendMode mode)
{
    SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
}

void Engine::DrawRect(SDL_Rect rect,Paint p,SDL_BlendMode mode)
{
    SDL_SetRenderDrawBlendMode(renderer,mode);
    SDL_SetRenderDrawColor(renderer,p.r,p.g,p.b,p.a);
    switch(rectMode)
    {
        case NONE:  SDL_RenderDrawRect(renderer,&rect);
                    break;

        case CENTER:    int x1,y1,x2,y2,w,h;
                        w = rect.w/2;
                        h = rect.h/2;
                        x1 = rect.x - w;
                        y1 = rect.y - h;
                        x2 = rect.x + w;
                        y2 = rect.y - h;
                        SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
                        x1 = rect.x - w;
                        y1 = rect.y - h;
                        x2 = rect.x - w;
                        y2 = rect.y + h;
                        SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
                        x1 = rect.x - w;
                        y1 = rect.y + h;
                        x2 = rect.x + w;
                        y2 = rect.y + h;
                        SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
                        x1 = rect.x + w;
                        y1 = rect.y - h;
                        x2 = rect.x + w;
                        y2 = rect.y + h;
                        SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
                        break;
    }
}

void Engine::FillRect(SDL_Rect rect,Paint p,SDL_BlendMode mode)
{
    SDL_SetRenderDrawBlendMode(renderer,mode);
    SDL_SetRenderDrawColor(renderer,p.r,p.g,p.b,p.a);
    switch(rectMode)
    {
        case NONE:  SDL_RenderFillRect(renderer,&rect);
                    break;

        case CENTER: rect.w /= 2;
                     rect.h /= 2;
                     SDL_RenderFillRect(renderer,&rect);
                     rect.w *= -1;
                     SDL_RenderFillRect(renderer,&rect);
                     rect.h *= -1;
                     SDL_RenderFillRect(renderer,&rect);
                     rect.w *= -1;
                     SDL_RenderFillRect(renderer,&rect);
                     break;
    }
}

void Engine::DrawShape(std::vector<Vec2d> points,Paint p,SDL_BlendMode mode)
{
    SDL_SetRenderDrawBlendMode(renderer,mode);
    SDL_SetRenderDrawColor(renderer,p.r,p.g,p.b,p.a);
    for(unsigned int i=0;i<points.size();i++)
    {
        unsigned int j = i+1;
        if(j == points.size())
            j = 0;
        SDL_RenderDrawLine(renderer,points[i].x,points[i].y,points[j].x,points[j].y);
    }
}

void Engine::DrawCircle(Vec2d point,float radius,Paint p,SDL_BlendMode mode)
{
    SDL_SetRenderDrawBlendMode(renderer,mode);
    SDL_SetRenderDrawColor(renderer,p.r,p.g,p.b,p.a);
    float x1 = radius + point.x;
    float y1 = point.y;
    for(float rad=0.1;rad<=2.01*M_PI;rad+=0.1)
    {
        float x2 = SDL_cos(rad)*radius + point.x;
        float y2 = SDL_sin(rad)*radius + point.y;
        SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
        x1 = x2;
        y1 = y2;
    }
}

void Engine::Background(Paint bgc)
{
    backgroundColor = bgc;
}

void Engine::render()
{
    SDL_SetRenderDrawColor(renderer,backgroundColor.r,backgroundColor.g,backgroundColor.b,255);
    SDL_RenderClear(renderer);

    draw();

    SDL_RenderPresent(renderer);
}

void Engine::run()
{
    while(running)
    {
        EventHandler();
        logic();
        render();
    }
}

float constrain(float f,float min,float max)
{
    f = (f<min)?min:f;
    f = (f>max)?max:f;
    return f;
}

float Dist(float x1,float y1,float x2,float y2)
{
    return SDL_sqrt(x1*x2 + y1*y2);
}

float map(float value,float min1,float max1,float min2,float max2)
{
    return min2 + (max2 - min2)*((value-min1)/(max1 - min1));
}
