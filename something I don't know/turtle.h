#include <SDL2/SDL.h>

#define black 0
#define white 1
#define red 2
#define green 3
#define blue 4
#define yellow 5

struct COLOUR
{
    Uint8 r,g,b;
};

class turtle
{
    float x,y,angle,Speed;
    SDL_Renderer* renderer;
    COLOUR bgcolour,pen_colour;
    COLOUR set_colour(int col);
public:
    turtle();
    turtle(int w,int h);
    ~turtle();
    void init_window(int w,int h);
    void forward(float dist,float angle);
    void clear();
    void pos(int x,int y);
    void background(int col);
    void pencolour(int col);
    void reset();
    void curve(int k);
};
