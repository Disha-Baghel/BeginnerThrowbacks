#include "Scratch/Scratch.h"

int main()
{
    Scratch::Window window(800,600,"hello");
    Scratch::Event event;
    bool running = true;

    while(running)
    {
        while(window.GetEvent(event))
        {
            switch(event.type)
            {
                case Scratch::QUIT: running = false; break;
            }
        }
    }

    return 0;
}
