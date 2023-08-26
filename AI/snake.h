#include <SDL2/SDL.h>

class Snake
{
    int time;
    enum {up=2,down=0,left=1,right=3} dir;
    SDL_Renderer* renderer;
    SDL_Event* event;
    SDL_Rect rect;
    void Event_Handler();
    void logic();
    float x,y,speed;
    SDL_Texture* snake_head;
    int angle;
public:
    Snake(SDL_Renderer* renderer,SDL_Event& event,SDL_Rect rect = {-1,0,0,0});
    void show();
    SDL_Rect get_rect();
    int get_direction();
    void set_direction(int d);
};
