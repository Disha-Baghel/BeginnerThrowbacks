#include <SDL2/SDL.h>

class Block
{
    SDL_Rect rect;
public:
    static SDL_Renderer* renderer;
    static int size;
    bool wall,path,end;
    int f,g,h;
    Block* parent;
public:
    Block(int x,int y);
    void draw();
    void set_pos(int x,int y);
    int get_x();
    int get_y();
};
