#include "Input.h"
#include "Engine2d.h"

Input* Input::Instance = nullptr;

Input::Input(){
    KeyStates = SDL_GetKeyboardState(nullptr);
}
void Input::Listen(){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT: Engine2d::GetInstance()->Quit(); break;
            case SDL_KEYDOWN: KeyDown(); break;
            case SDL_KEYUP: KeyUp(); break;
        }
    }
}

bool Input::GetKeydown(SDL_Scancode key){
    return (KeyStates[key] == 1);
}

void Input::KeyUp(){
    KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown(){
    KeyStates = SDL_GetKeyboardState(nullptr);
}
