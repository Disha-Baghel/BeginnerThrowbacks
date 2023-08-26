#include <SDL2/SDL.h>
#include "Dino.h"
#include "Text.h"

class Application
{
    SDL_Renderer* renderer;
    SDL_Window* window;
    Application();
    ~Application();
    bool running;
    static Application* Application_instance;
    Dino* dino;
    Text* text;
    void EventHandler();
    float score,high_score;
public:
    static Application* Instance();
    bool loop();
};
