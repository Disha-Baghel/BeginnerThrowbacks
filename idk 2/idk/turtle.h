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
    void forward_for_circle(float dist,float angle);
public:
    turtle();
    turtle(int w,int h);
    ~turtle();
    void init_window(int w,int h);
    void forward(float dist,float angle);
    void backward(float dist,float angle);
    void speed(int Speed);
    void clear();
    void pos(int x,int y);
    void background(int col);
    void pencolour(int col);
    void reset();
    void circle(int radius);
};
