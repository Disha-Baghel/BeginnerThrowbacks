#include "Engine.h"
#include "cell.h"

class Game: public Engine
{
    Cell** board;
    Cell** next;
public:
    Game();
    void logic();
    void draw();
    void onKeyClick();
    void onMouseClick();
};
