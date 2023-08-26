#include "ImageLoad.h"
#include "cloud.h"
#include <stdlib.h>
#include <time.h>

cloud::cloud()
{
    this->renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));
    srand(time(NULL));
    y = rand()%150 + 50;
    velocity = rand()%2 + 1;
    cloud_rect = {800,y,90,50};
}

cloud::~cloud()
{

}

void cloud::show()
{
    cloud_rect.x-=velocity;
    show_image(renderer,"cloud.png",cloud_rect);
}

int cloud::get_x()
{
    return cloud_rect.x;
}
