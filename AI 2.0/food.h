#include <SDL2/SDL.h>
#include "image.h"

class Food
{
    SDL_Rect rect;
    static int prev_x,prev_y;
    SDL_Texture* food;
    static SDL_Renderer* renderer;
    static int size;
public:
    static void init(SDL_Renderer* renderer,int size);
    Food();
    void draw();
    SDL_Rect& get_rect();
};
