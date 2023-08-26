#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

class Input
{
    public:
        static Input* GetInstance(){
            return Instance = (Instance != nullptr)?Instance: new Input();
        }

        void Listen();
        bool GetKeydown(SDL_Scancode key);

    private:
        Input();
        void KeyUp();
        void KeyDown();

        const Uint8* KeyStates;
        static Input* Instance;
};

#endif // INPUT_H
