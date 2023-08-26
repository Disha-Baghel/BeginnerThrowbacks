#pragma once

#include <SDL2/SDL.h>

struct Paint{
    int r=0,g=0,b=0,a=0;
};

class Engine
{
    SDL_Window* window;
    static SDL_Renderer* renderer;
    SDL_Event event;
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
    static void Show(){SDL_RenderPresent(renderer);};
    static void DrawPoint(int x,int y,Paint p={255,255,255,255},SDL_BlendMode mode = SDL_BLENDMODE_NONE);

    void run();
};
