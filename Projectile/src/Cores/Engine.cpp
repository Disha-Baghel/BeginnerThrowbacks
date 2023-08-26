#include "Engine.h"
#include "Body.h"

Engine* Engine::Instance = nullptr;
Body* body;
Vec2D Initial_velocity;

Engine::Engine(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(800,500,0,&window,&renderer);
    running = true;
    body = new Body(0,480,20,20,{255,255,255,255});
    Initial_velocity = VecAtAngle(0.2,45);
    body->SetVelocity(Initial_velocity);
}

void Engine::EventListener(){
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT: running = false;break;
        }
    }
}

void Engine::Update(){
    body->ApplyForce({0,0.0001});
    body->Update();
}

void Engine::Render(){
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    body->Render(renderer);

    SDL_RenderPresent(renderer);
}

void Engine::Start(){
    while(running){
        EventListener();
        Update();
        Render();
    }
}
