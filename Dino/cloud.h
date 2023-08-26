#pragma once

#include <SDL2/SDL.h>

class cloud
{
    SDL_Renderer* renderer;
    SDL_Rect cloud_rect;
    int y,velocity;
public:
    cloud();
    ~cloud();
    void show();
    int get_x();
};
