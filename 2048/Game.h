#include <SDL2/SDL.h>

class Game
{
    enum {down,left,up,right}dir;
    SDL_Renderer* renderer;
    SDL_Window* window;
    static Game* Game_instance;
    bool running;
    Game();
    void EventHandler();
    void logic();
    void render();
    SDL_Event event;
    int arr[4][4];
    void set_color(int col);
    void set_random_pos();
    bool changed;
public:
    ~Game();
    static Game* Instance();
    bool loop();
};
