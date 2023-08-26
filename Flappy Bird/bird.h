#include <SDL2/SDL.h>

#define width 800
#define height 700

class bird
{
    SDL_Texture* bird1,*bird2,*bird3;
    SDL_Renderer *renderer;
    const float grav = 0.6;
    const float up = -15;
    float velocity;
    SDL_Rect birdRect;
public:
    int size;
    int x,y;
    bird(SDL_Renderer*,int);
    void drawbird();
    void gravity();
    void lift();
};
