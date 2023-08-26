#include "InputManager.h"

InputManager* InputManager::m_Instance;

InputManager::InputManager()
{
    for(int i=0;i<256;i++)
        m_Keys[i] = false;
}

int InputManager::Handle()
{
    unsigned int ret = -1;
    while(SDL_PollEvent(&m_Event))
    {
        switch(m_Event.type)
        {
        case SDL_QUIT: ret = CLOSED;
                    break;

        case SDL_KEYDOWN:
                m_Keys[m_Event.key.keysym.sym] = true; break;
        case SDL_KEYUP:
                m_Keys[m_Event.key.keysym.sym] = false; break;

        case SDL_WINDOWEVENT:
            if(m_Event.window.event == SDL_WINDOWEVENT_RESIZED)
                ret = RESIZED;
        }
    }

    return ret;
}
