#include "Pattern.h"
#include <iostream>

Pattern::Pattern()
{
    j = k = 1;
    pat = pattern1;
    this->running = true;
    vikram.pencolour(red);
    vikram.speed(0);
}

void Pattern::EventHandler()
{
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_KEYDOWN:

            switch(event.key.keysym.sym)
            {
            case SDLK_1:
                pat = pattern1;
                break;
            case SDLK_2:
                pat = pattern2;
                break;
            case SDLK_3:
                pat = pattern3;
                break;
            }
        }
    }
}

bool Pattern::loop()
{
    EventHandler();

    switch(pat)
    {
    case pattern1:
        Pattern1();
        break;
    case pattern2:
        Pattern2();
        break;
    case pattern3:
        Pattern3();
        break;
    }

    return running;
}

void Pattern::Pattern1()
{
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_LEFT:
                if(j>1)
                    j--;
                break;
            case SDLK_RIGHT:
                j++;
                break;
            }
        }


        vikram.clear();
        vikram.pencolour(red);
        vikram.pos(400,250);
        for(int i=0; i<200; i++)
        {
            vikram.forward(i,i*j);
            vikram.backward(j,i*j);
        }

        vikram.present();
    }
}

void Pattern::Pattern2()
{
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_LEFT:
                if(k>1)
                    k--;
                break;
            case SDLK_RIGHT:
                k++;
                break;
            }
        }

        vikram.clear();
        vikram.pencolour(red);
        vikram.pos(400,250);
        for(int i=0; i<200; i++)
            vikram.forward(i,i*k);

        vikram.present();
    }
}

void Pattern::Pattern3()
{
    int a = 1;
    int b = 1;

    int q = 5;
    while(q--)
    {
        vikram.pencolour(((q+1) % 4) + 2);
        int spike_count = 1;

        for(int k=0; k<4; ++k)
        {
            b*=-1;
            if(k==2)
                a*=-1;

            vikram.pos(400 + 100*a, 250 + 100*b);

            for(int j=0; j<9*spike_count; ++j)
                for(int i=0; i<4; ++i)
                    vikram.forward(50,90*i - j*40/spike_count);

            spike_count++;
        }

        vikram.present();
    }

    pat = pattern1;
}
