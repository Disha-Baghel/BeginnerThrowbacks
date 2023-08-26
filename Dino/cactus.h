#include "ImageLoad.h"

class cactus
{
    SDL_Renderer* renderer;
    float x;
    SDL_Rect cactus_rect;
public:
    cactus();
    ~cactus();
    void show();
    static float velocity;
    int get_x();
    bool has_intersection(SDL_Rect rect);
    void inc_x();
};
