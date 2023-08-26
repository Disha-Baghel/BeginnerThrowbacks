#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Image.h"
#include "MathsVector.h"

struct Paint
{
    uint8_t r=0,g=0,b=0,a=255;
};

float constrain(float f,float min,float max);
float Dist(float x1,float y1,float x2,float y2);
float map(float value,float min1,float max1,float min2,float max2);

class Engine
{
    SDL_Window* window;
    static SDL_Renderer* renderer;
    SDL_Event event;
    static RectMode rectMode;
    static Paint backgroundColor;
    void EventHandler();
    bool running;
    void render();
protected:
    void CreateWindow(int width,int height);
    virtual void logic() = 0;
    virtual void draw() = 0;
    virtual void onKeyClick() = 0;
    virtual void onMouseClick() = 0;
public:
    int mouseX,mouseY;
    int WIDTH,HEIGHT;
    static void setRectMode(RectMode rm);
    static void Background(Paint bgc);
    static void Drawline(int x1,int y1,int x2,int y2,Paint p={255,255,255,255},SDL_BlendMode mode = SDL_BLENDMODE_NONE);
    static void DrawRect(SDL_Rect rect,Paint p={255,255,255,255},SDL_BlendMode mode = SDL_BLENDMODE_NONE);
    static void FillRect(SDL_Rect rect,Paint p={255,255,255,255},SDL_BlendMode mode = SDL_BLENDMODE_NONE);
    static void DrawCircle(Vec2d point,float radius,Paint paint={255,255,255,255},SDL_BlendMode mode = SDL_BLENDMODE_NONE);
    //Points should be clockwise or anti-clockwise
    static void DrawShape(std::vector<Vec2d> points,Paint p={255,255,255,255},SDL_BlendMode mode = SDL_BLENDMODE_NONE);

    void run();
};
