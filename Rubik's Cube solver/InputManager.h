#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL.h>

#define Input (*InputManager::GetInstance())

class InputManager
{
public:
    InputManager();
    int Handle();

    const SDL_Event& GetEvent() const { return m_Event;}
    const bool& KeyDown(unsigned char key) const { return m_Keys[key];}

    static InputManager* GetInstance() { return m_Instance = (m_Instance != nullptr)? m_Instance: new InputManager();}

    enum
    {
        CLOSED,
        RESIZED
    };

private:
    SDL_Event m_Event;

    bool m_Keys[256];

    static InputManager* m_Instance;
};

#endif // INPUTMANAGER_H
