#include <SDL2/SDL.h>
#include <vector>

class Snake
{
    SDL_Renderer* renderer;
    std::vector<SDL_Rect> body;
    float x_pos,y_pos;
    int step;
    int size;
    SDL_Rect FoodRect;
public:
    Snake(SDL_Renderer* renderer,int size);
    void Eat();
    void draw();
    void logic();
    SDL_Rect get_head();
    void getPath(std::vector<SDL_Rect> Path);
    std::vector<SDL_Rect> getBody();
    std::vector<SDL_Rect> Path;
};
