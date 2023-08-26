#include <SDL2/SDL.h>

class Pipe
{
    SDL_Texture* pipeTexture[4];
    int speed;
    SDL_Rect pipe1;
    SDL_Rect pipe2;
    SDL_Rect Background;
    SDL_Renderer *renderer;
public:
    int top;
    int bottom;
    int x;
    int w;
    Pipe(SDL_Renderer*);
    void drawpipe();
    void pipeUpdate();
    bool offScreen();
    bool highlight;
};
