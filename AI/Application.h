#include <SDL2/SDL.h>
#include <vector>
#include "snake.h"
#include "food.h"

class Game
{
    enum {width = 800,height = 500};
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_bool running;
    static Game* Game_Instance;
    void Event_Handler();
    void logic();
    Snake* snake;
    Food* food;
    SDL_Event event;
    int score;
    std::vector<std::pair<SDL_Rect,int>> body;
    SDL_Texture *Body,*Tail_end,*Tail_turn;
    bool reached_x;
public:
    Game();
    ~Game();
    static Game* Instance();
    bool loop();
};
