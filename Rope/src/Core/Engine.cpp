#include "Engine.h"
#include"Event.h"

bool Engine::CreateCanvas(int width,int height,const char* AppName){
    Width = width;
    Height = height;
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        SDL_Log("Failed to initialize SDL2: %s",SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow(AppName,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,Width,Height,0);
    if(window == nullptr){
        SDL_Log("Failed to Create Window: %s",SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr){
        SDL_Log("Failed to create Renderer: %s",SDL_GetError());
        return false;
    }

    BgCol = {0,0,0,255};

    return running = true;
}

bool Engine::KeyPressed(SDL_Scancode sc){
    return Event::GetInstance()->isKeyPressed(sc);
}

bool Engine::KeyPressed(SDL_Keycode kd){
    return Event::GetInstance()->isKeyPressed(kd);
}

bool Engine::KeyPressed(const char* key){
    return Event::GetInstance()->isKeyPressed(key);
}

void Engine::Render(){
    SDL_SetRenderDrawColor(renderer,BgCol.r,BgCol.g,BgCol.b,BgCol.a);
    SDL_RenderClear(renderer);

    Draw();

    SDL_RenderPresent(renderer);
}

void Engine::Start(){
    while(running){
        Event::GetInstance()->Listen(running);
        Event();
        Update();
        Render();
    }
}
