#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>

class Engine{

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    static Engine* Instance;
    bool running;
    void EventListener();
    void Update();
    void Render();
    Engine();
public:
    static Engine* GetInstance(){return Instance = (Instance != nullptr)?Instance: new Engine;}
    void Start();
};

#endif // ENGINE_H
