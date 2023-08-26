#include <iostream>
#include "Play.h"

int main(int argc, char* argv[]){

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
			return 1;
    SDL_CreateWindow("Audio",100,100,100,100,0);

    SDL_Event event;
    bool running = true;

    while(running)
    {
        if(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_a: play("mus.wav");break;
                    }
            }
        }
    }

	return 0;
}
