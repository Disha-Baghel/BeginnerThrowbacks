#include "Engine.h"
#include "Vehicle.h"

class Game: public Engine
{
    Vehicle* v;
public:
    Game();
    void logic();
    void draw();
    void onKeyClick();
    void onMouseClick();
};
