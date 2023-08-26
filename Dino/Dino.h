#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "cloud.h"
#include "cactus.h"

class Dino
{
    float x1,x2,y,forward_velocity;
    SDL_Rect Dino_rect;
    bool jump;
    float velocity,gravity;
    SDL_Renderer* renderer;
    void EventHandler();
    void logic();
    std::vector<cloud*> clouds;
    std::vector<cactus*> Cactus;
public:
    Dino();
    ~Dino();
    void show();
    static SDL_Event event;
    static bool Game_started;
};
