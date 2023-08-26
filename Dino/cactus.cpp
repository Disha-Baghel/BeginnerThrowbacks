#include "cactus.h"
#include "ImageLoad.h"

float cactus::velocity = 1.5;

cactus::cactus()
{
    x = 800;
    renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));
    cactus_rect = {(int)x,286,30,70};
}

cactus::~cactus()
{

}

void cactus::show()
{
    x -= velocity;
    cactus_rect = {(int)x,286,30,70};
    show_image(renderer,"cactus.png",cactus_rect);
}

int cactus::get_x()
{
    return x;
}

void cactus::inc_x()
{
    x++;
}

bool cactus::has_intersection(SDL_Rect rect)
{
    return SDL_HasIntersection(&rect,&cactus_rect);
}
