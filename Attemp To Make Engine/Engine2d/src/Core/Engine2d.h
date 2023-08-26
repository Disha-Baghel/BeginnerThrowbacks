#ifndef ENGINE2D_H
#define ENGINE2D_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 800
#define HEIGHT 500


class Engine2d {
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    bool Init();
    void EventHandler();
    void Update();
    void Draw();
    static Engine2d* Instance;
  public:
    static Engine2d* GetInstance();
    SDL_Renderer* GetRenderer() {
        return renderer;
    }
    void Start();
    void Clear();
    void Quit();
};

#endif // ENGINE2D_H
