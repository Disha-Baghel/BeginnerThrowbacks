#include "InputManager.h"
#include <SDL2/SDL.h>

InputManager* InputManager::m_Instance;

InputManager::InputManager()
{
    for(int i=0;i<256;i++)
        m_keys[i] = false;
}

int InputManager::Handle()
{
    while(SDL_PollEvent(&m_event))
    {
        switch(m_event.type)
        {
        case SDL_QUIT:
            return CLOSED;
            break;
        case SDL_KEYDOWN:
            m_keys[m_event.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            m_keys[m_event.key.keysym.sym] = false;
            break;
        }

        if(m_event.window.event == SDL_WINDOWEVENT_RESIZED)
            return RESIZED;
    }

    return -1;
}
