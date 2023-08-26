#include "Timer.h"
#include <SDL2/SDL.h>

Timer* Timer::Instance = nullptr;

void Timer::Tick(){
    DeltaTime = (SDL_GetTicks() - LastTime)*(TARGET_FPS/1000.0f);

    if(DeltaTime > TARGET_DELTATIME)
        DeltaTime = TARGET_DELTATIME;

    LastTime = SDL_GetTicks();
}
