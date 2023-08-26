#include "Game.h"

int main(int argc,char** argv)
{
    Game::Instance()->loop();
    return 0;
}
