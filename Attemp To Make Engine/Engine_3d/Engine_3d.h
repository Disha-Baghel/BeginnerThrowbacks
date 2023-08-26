#include <SDL2/SDL.h>
#include "object.h"

class Engine_3d
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    int width,height;
    bool running;
    void update(void (*DrawCallBack)(void));
    void EventHandler();
    mat4x4 matProj;
    vec3d vCamera = {0,0,0};
public:
    Engine_3d(int width=800,int height=500);
    ~Engine_3d();
    void Start(void (*DrawCallBack)(void));
};
