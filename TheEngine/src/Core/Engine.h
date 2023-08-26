#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <string>
#include "Shape.h"

class Engine: protected Shape{
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    Color BgCol;
    void Render();
protected:
    Engine(){}
    int Width,Height;
    virtual void Event(){}
    virtual void Update(){};
    virtual void Draw() = 0;
    bool KeyPressed(SDL_Scancode sc);
    bool KeyPressed(SDL_Keycode kc);
    bool KeyPressed(const char* key);
    bool CreateCanvas(int width,int height,const char* AppName = "Engine");
    void Background(Color BgCol){this->BgCol = BgCol;}
public:
    void Start();
};

#endif // ENGINE_H
