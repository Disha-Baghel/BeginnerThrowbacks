#include "game.h"
#include "menu.h"

int main(int argc,char** argv)
{
    game Snake_game;
    menu Main_Menu;
    Main_Menu.getRenderer(Snake_game.renderer);

    while(Main_Menu.run)
    {

        if(!Snake_game.gameover)
            Snake_game.mainLoop();

        else
            Main_Menu.loop();

        if(Snake_game.run == false)
            Main_Menu.run = false;

        if(Main_Menu.gameover == false)
            Snake_game.gameover = false;
    }

    return 0;
}
