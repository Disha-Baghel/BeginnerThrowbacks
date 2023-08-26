#include "Event.h"

Event* Event::Instance = nullptr;

void Event::Listen(bool& running){
    ScanCode = SDL_SCANCODE_UNKNOWN;
    KeyCode = SDLK_UNKNOWN;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT: running = false;break;
            case SDL_KEYDOWN:
                                ScanCode = event.key.keysym.scancode;
                                KeyCode = event.key.keysym.sym;
                                break;
        }
    }
}

bool Event::isKeyPressed(SDL_Scancode sc){
    return ScanCode == sc;
}

bool Event::isKeyPressed(SDL_Keycode kd){
    return KeyCode == kd;
}

bool Event::isKeyPressed(const char* key){
    return SDL_GetKeyName(KeyCode) == key;
}
