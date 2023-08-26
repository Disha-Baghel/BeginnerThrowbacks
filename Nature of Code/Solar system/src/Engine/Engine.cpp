#include "Engine.h"
#include "Planet/Planet.h"
#include "Sun/Sun.h"

Engine* Engine::Instance = nullptr;
Planet* venus;
Planet* earth;
Planet* mars;
Planet* jupiter;
Sun* sun;

Engine::Engine(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(800,500,0,&window,&renderer);
    running = true;


    SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_ADD);

    venus = new Planet(500,250,10,{255,0,0,255});
    earth = new Planet(550,250,10,{0,255,0,255});
    mars = new Planet(600,250,8,{255,255,255,255});
    jupiter = new Planet(700,250,25,{255,255,255,255});
    sun = new Sun(400,250,50,{255,255,0,255});

    sun->SetMass(2.5);

    venus->SetMass(0.49);
    venus->SetVelocity(Vec2d(0,0.15));

    earth->SetMass(0.5);
    earth->SetVelocity(Vec2d(0,0.3));

    mars->SetMass(0.4);
    mars->SetVelocity(Vec2d(0,0.4));

    jupiter->SetMass(0.8);
    jupiter->SetVelocity(Vec2d(0,0.6));
}

void Engine::EventListener(){
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT: running = false;break;
            case SDL_KEYDOWN: if(Planet::isShowTrace())
                                    Planet::ShowTrace(false);
                                else
                                    Planet::ShowTrace(true);
                                break;
        }
    }
}

void Engine::Update(){

    sun->Attract(venus);
    sun->Attract(earth);
    sun->Attract(mars);
    sun->Attract(jupiter);

    sun->Update();
    venus->Update();
    earth->Update();
    mars->Update();
    jupiter->Update();
}

void Engine::Render(){
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    sun->Render(renderer);
    venus->Render(renderer);
    earth->Render(renderer);
    mars->Render(renderer);
    jupiter->Render(renderer);

//    SDL_RenderDrawLine(renderer,earth->GetPosition().x,earth->GetPosition().y,venus->GetPosition().x,venus->GetPosition().y);
//    SDL_RenderDrawLine(renderer,earth->GetPosition().x,earth->GetPosition().y,mars->GetPosition().x,mars->GetPosition().y);
//    SDL_RenderDrawLine(renderer,jupiter->GetPosition().x,jupiter->GetPosition().y,mars->GetPosition().x,mars->GetPosition().y);

    SDL_RenderPresent(renderer);
}

void Engine::Start(){
    while(running){
        EventListener();
        Update();
        Render();
    }
}
