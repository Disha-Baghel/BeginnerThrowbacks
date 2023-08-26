#include <vector>
#include <SDL2/SDL.h>

struct Map
{
    SDL_Rect rect;
    bool wall=false;
    int f=0,g=0,h=0;
    Map* parent;
};

std::vector<SDL_Rect> FindPath(SDL_Rect start,SDL_Rect Dest,std::vector<SDL_Rect> body);
