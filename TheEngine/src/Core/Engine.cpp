#include <SDL2/SDL_image.h>
#include "Engine.h"
#include "Event.h"
#include "Image.h"

bool Engine::CreateCanvas(int width,int height,const char* AppName){
    Width = width;
    Height = height;

    try{
        if(SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_PNG) != 0){
            throw SDL_GetError();
        }
        window = SDL_CreateWindow(AppName,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,Width,Height,0);
        if(window == nullptr){
            throw SDL_GetError();
        }
        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        if(renderer == nullptr){
            throw SDL_GetError();
        }
    }catch(const char* Error){
        SDL_Log(Error);
        return false;
    }

    BgCol = {0,0,0,255};
    Image::SetRenderer(renderer);

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
        Push();
        Event::GetInstance()->Listen(running);
        Event::GetInstance()->GetMouseState(MouseX,MouseY);
        Event();
        Update();
        Render();
        Pop();
    }
}
