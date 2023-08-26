#include "Engine.h"

class Game: public Engine
{
    bool board[500][800];
    bool** next;
public:
    Game();
    void logic();
    void draw();
    void onKeyClick();
    void onMouseClick();
};
