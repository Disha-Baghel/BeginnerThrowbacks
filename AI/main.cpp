#include "Application.h"

int main(int argc,char** argv)
{
    while(Game::Instance()->loop());

    return 0;
}
