#include "turtle.h"

enum PAT {pattern1,pattern2,pattern3};

class Pattern
{
    int j,k;
    PAT pat;
    turtle vikram;
    bool running;
    SDL_Event event;
public:
    Pattern();
    bool loop();
    void EventHandler();
    void Pattern1();
    void Pattern2();
    void Pattern3();
};
