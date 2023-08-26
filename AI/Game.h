#include <SDL2/SDL.h>
#include "snake.h"
#include "food.h"

class Game
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    const int width = 800;
    const int height = 500;
    static Game* Game_Instance;
    bool running;
    Snake* snake;
    Food* food;
private:
    Game();
    void EventHandler();
    void logic();
    void draw();
public:
    static Game* Instance();
    void Start();
};
