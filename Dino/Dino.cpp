#include <SDL2/SDL.h>
#include "ImageLoad.h"
#include "Dino.h"
#include <iostream>

SDL_Event Dino::event;
bool Dino::Game_started;

Dino::Dino()
{
    velocity = 5;
    gravity = 0.09;
    Dino_rect = {50,300,50,50};
    renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));
    Game_started = jump = false;
    x1 = 0;
    x2 = 800;
    y = 300;
}

Dino::~Dino()
{

}

void Dino::logic()
{
    x1-=cactus::velocity;
    x2-=cactus::velocity;
    if(x1 < - 800)
        x1 = 800;
    else if(x2 < -800)
        x2 = 800;

    if(jump)
    {
        velocity -= gravity;
        y -= velocity;
        Dino_rect.y = y;
    }

    if(y > 300)
    {
        velocity = 5;
        jump = false;
    }

    if(SDL_GetTicks() % 1000 == 0)
        clouds.push_back(new cloud());

    {
        again:
        if(SDL_GetTicks() % 700 == 0)
            Cactus.push_back(new cactus());

        if(Cactus.size() > 1)
        if(Cactus[Cactus.size()-1]->get_x() - Cactus[Cactus.size()-2]->get_x() < 200)
        {
            Cactus.pop_back();
            goto again;
        }
    }
}

void Dino::show()
{
    EventHandler();

    if(!Game_started)
        show_image(renderer,"Dino.png",Dino_rect);
    else
    {
        logic();

        for(unsigned int i=0;i<clouds.size();i++)
        {
            if(clouds[i]->get_x() < -100)
            {
                std::swap(clouds[i],clouds[clouds.size() - 1]);
                clouds.pop_back();
            }

            clouds[i]->show();
        }

        show_image(renderer,"road.png",{(int)x1,340,800,20});
        show_image(renderer,"road.png",{(int)x2,340,800,20});


        for(unsigned int i=0;i<Cactus.size();i++)
        {
            if(Cactus[i]->get_x() < -100)
            {
                std::swap(Cactus[i],Cactus[Cactus.size() - 1]);
                Cactus.pop_back();
            }

            if(Cactus[i]->has_intersection(Dino_rect))
                Game_started = false;

            Cactus[i]->show();
        }

        int frequency = 1000/13;
        int time = (SDL_GetTicks()/frequency)%2;

        if(jump)
            time = 1;

        switch(time)
        {
            case 0:show_image(renderer,"Dino_running_1.png",Dino_rect);break;
            case 1:show_image(renderer,"Dino_running_2.png",Dino_rect);break;
        }
    }
}

void Dino::EventHandler()
{
    switch(event.type)
    {
    case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
            case SDLK_SPACE: if(!Game_started)
                                Game_started = true;
                            else if(!jump)
                                jump = true;
                            break;
        }
    }
}
