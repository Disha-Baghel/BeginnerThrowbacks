#ifndef EVENT_H
#define EVENT_H

#include <SDL2/SDL_events.h>

class Event
{
    SDL_Event event;
    static Event* Instance;
    Event(){}
    SDL_Scancode ScanCode;
    SDL_Keycode KeyCode;
    Uint8 Button;
public:
    static Event* GetInstance(){return Instance = (Instance != nullptr)?Instance: new Event();}
    void Listen(bool& running);
    bool MouseButtonLeft();
    bool isKeyPressed(SDL_Scancode sc);
    bool isKeyPressed(SDL_Keycode kd);
    bool isKeyPressed(const char* key);
    void GetMouseState(int& MouseX,int& MouseY);
};

#endif // EVENT_H
