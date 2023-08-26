#include <SDL2/SDL.h>
#include "Block.h"
#include <vector>

class Game
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    static Game* Game_Instance;
    static const int width = 800,height = 500;
    static const int Block_size = 20;;
    static const int rows = height/Block_size;
    static const int cols = width/Block_size;
    bool running;
    Block* block[rows][cols];
    int x_pos,y_pos;
private:
    Game();
    void EventHandler();
    void logic();
    void draw();
    std::vector<Block*> Neighbors(Block* b);
    float CalculateH(Block* elem,Block* dest);
public:
    static Game* Instance();
    void loop();
};
