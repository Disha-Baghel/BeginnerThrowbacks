#include <vector>
#include "pipe.h"
#include "bird.h"

class game
{
    game();
    ~game();
    static game* GameInstance;
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    void EventHandler();
    void update();
    void display();
    bird* brd;
    std::vector<Pipe> pipe;
public:
    static game* Instance();
    bool run();
    void loop();
};
