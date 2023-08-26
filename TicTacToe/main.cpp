#include "Game.h"

int main(int argc,char** argv)
{
    while(Game::instance()->loop());

    return 0;
}
