#include <SDL2/SDL.h>

class Food
{
    SDL_Rect rect;
    SDL_Renderer* renderer;
    static SDL_Texture* food;
public:
    Food(SDL_Renderer* renderer);
    void show();
    SDL_Rect get_rect();
};
