#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL.h>

#define InputInstance InputManager::GetInstance()

// Right now, making a singleton class
// Later will try to implement command pattern

class InputManager
{
    public:
        int Handle();

        bool KeyDown(int key) { return m_keys[key];}


        static InputManager* GetInstance() {return m_Instance = (m_Instance!=nullptr)?m_Instance: new InputManager(); }

        enum
        {
            CLOSED,
            RESIZED
        };
    protected:

    private:
        InputManager();
        SDL_Event m_event;

        int m_keys[256];

        static InputManager* m_Instance;
};

#endif // INPUTMANAGER_H
