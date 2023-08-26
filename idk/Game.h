#include "Engine.h"
#include "cell.h"

class Game: public Engine
{
    cell* c[800][500];
public:
    Game();
    void logic();
    void draw();
    void onKeyClick();
    void onMouseClick();
};
