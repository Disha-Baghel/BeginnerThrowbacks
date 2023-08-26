#include "game.h"

int main(int argc,char** argv)
{
    while(game::Instance()->run())
        game::Instance()->loop();

    return 0;
}
