#include "game.h"

game* game::GameInstance = new game();

game* game::Instance()
{
    if(game::GameInstance == nullptr)
        game::GameInstance = new game();
    return game::GameInstance;
}

game::game()
{
    this->running = true;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_CreateWindowAndRenderer(width,height,0,&window,&renderer);
    SDL_SetWindowTitle(window,"Flappy Bird");

    brd = new bird(renderer,30);
    pipe.push_back(Pipe(renderer));
}

void game::EventHandler()
{
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT: this->running = false;break;
            case SDL_KEYDOWN:
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_SPACE: brd->lift();break;
                    }
                }
        }
    }
}

void game::update()
{
    brd->gravity();

    for(Uint8 i=0;i < pipe.size() - 1;i++)
    {
        pipe[i].pipeUpdate();

        if(brd->y + brd->size < pipe[i].top || brd->y > height - pipe[i].bottom)
             if(brd->x < pipe[i].x && brd->x > pipe[i].x - pipe[i].w)
             {
                 pipe[i].highlight = true;
             }


        if(pipe[i].offScreen() || pipe.size() > 10)
        {
            pipe.erase(pipe.begin());
        }
    }
}

void game::display()
{
    SDL_SetRenderDrawColor(renderer,135, 206, 235,255);
    SDL_RenderClear(renderer);

    if(SDL_GetTicks() % 500 ==0)
        pipe.push_back(Pipe(renderer));

    for(Uint8 i=0;i < pipe.size() - 1;i++)
        pipe[i].drawpipe();

    brd->drawbird();

    SDL_RenderPresent(renderer);
}

void game::loop()
{
    EventHandler();

    int a = SDL_GetTicks() % (1000/60);
    if(a == 0)
    {
        update();
        display();
    }
}

bool game::run()
{
    return this->running;
}

game::~game()
{
    SDL_Quit();
}
