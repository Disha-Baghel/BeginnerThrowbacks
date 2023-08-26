#include <SDL2/SDL.h>
#include <vector>
#include "Boundary.h"
#include "Particle.h"

class Game
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    static const int width = 800;
    static const int height = 500;
    static const int SceneW = width/2;
    bool running;
    static Game* GameInstance;
    std::vector<Boundary*> walls;
    Particle* particle;
private:
    Game();
    ~Game();
    void EventHandler();
    void logic();
    void draw();
public:
    static Game* Instance();
    void start();
};
