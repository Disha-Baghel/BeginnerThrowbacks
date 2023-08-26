#include "Engine2d.h"
#include "TextureManager.h"
#include "Warrior.h"
#include "Input.h"
#include "Timer.h"

Engine2d* Engine2d::Instance = nullptr;
Warrior* player = nullptr;

Engine2d* Engine2d::GetInstance() {
    return Instance = (Instance != nullptr)?Instance:new Engine2d();
}

bool Engine2d::Init() {

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_PNG) != 0) {
        SDL_Log("Failed to initialize: %s",SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("Engine2d",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0);
    if(window == nullptr) {
        SDL_Log("Failed to create window: %s",SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr) {
        SDL_Log("Failed to create renderer: %s",SDL_GetError());
        return false;
    }

    TextureManager::GetInstance()->Load("player","asset\\v2.1\\adventurer-1.3-Sheet.png");
    player = new Warrior(new Properties("player",200,200,50,45));

    return running = true;
}

void Engine2d::EventHandler() {
    Input::GetInstance()->Listen();
}

void Engine2d::Update() {
    float dt = Timer::GetInstance()->GetDeltatime();
    player->update(dt);
}

void Engine2d::Draw() {
    SDL_SetRenderDrawColor(renderer,127,134,230,255);
    SDL_RenderClear(renderer);

    player->Draw();

    SDL_RenderPresent(renderer);
}

void Engine2d::Clear() {
    TextureManager::GetInstance()->Clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void Engine2d::Start() {
    if(Init()) {
        while(running) {
            EventHandler();
            Update();
            Draw();
            Timer::GetInstance()->Tick();
        }
    }
}
void Engine2d::Quit()
{
    this->running = false;
}
