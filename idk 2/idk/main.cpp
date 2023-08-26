#include "turtle.h"

int main(int agc,char** argv)
{
    turtle vikram;
    vikram.pencolour(red);
    vikram.speed(0);

    SDL_Event event;
    int j=0;

    while(1)
    {
        if(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_LEFT: if(j>1)
                                        j--;break;
                    case SDLK_RIGHT: j++;break;
                }
            }

            vikram.clear();
            vikram.pencolour(red);
            vikram.pos(400,250);
            for(int i=0;i<200;i++)
                vikram.forward(i,i*j);
        }
    }

//    int a = 1;
//    int b = 1;
//
//    int q = 5;
//    while(q--)
//    {
//        vikram.pencolour(((q+1) % 4) + 2);
//        int spike_count = 1;
//
//        for(int k=0;k<4;++k)
//        {
//            b*=-1;
//            if(k==2)
//                a*=-1;
//
//            vikram.pos(400 + 100*a, 250 + 100*b);
//
//            for(int j=0;j<9*spike_count;++j)
//                for(int i=0;i<4;++i)
//                    vikram.forward(50,90*i - j*40/spike_count);
//
//            spike_count++;
//        }
//    }

    return 0;
}
