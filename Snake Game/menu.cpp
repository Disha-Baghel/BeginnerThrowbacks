#include "menu.h"

menu::menu()
{
    IMG_Init(IMG_INIT_PNG);
    Menu_still = IMG_Load("image/Main_Menu.png");
    Menu_start = IMG_Load("image/Main_Menu_Start.png");
    Menu_quit = IMG_Load("image/Main_Menu_Quit.png");

    run = true;
    gameover = true;
    Current_surf = Menu_still;

}

void menu::image()
{
    Texture = SDL_CreateTextureFromSurface(renderer,Current_surf);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,Texture,NULL,NULL);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(Texture);
}

void menu::eventListener()
{
    if(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            run = false;
        }

        else if( event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_GetMouseState(&x,&y);

            if(x >= 185 && x <= 615&& y >= 200 && y <= 250)
            {
                Current_surf = Menu_start;
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    gameover = false;
                }
            }
            else if(x >= 185 && x <= 615&& y >= 285 && y <= 335)
            {
                Current_surf = Menu_quit;
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    run = false;
                }
            }
            else
                Current_surf = Menu_still;
        }
    }
}

void menu::getRenderer(SDL_Renderer *r)
{
    renderer = r;
}

void menu::loop()
{

    eventListener();
    image();
}

menu::~menu()
{
    IMG_Quit();
}
