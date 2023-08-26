#include "Button.h"
#include "Image.h"
#include "Event.h"
#include <iostream>

ButtonContainer* ButtonContainer::Instance = nullptr;

void ButtonContainer::Create(std::string ButtonId,Button* btn){
    ButtonMap[ButtonId] = btn;
    Image::GetInstance()->Load("Button_" + ButtonId,btn->GetImageSource());
    Image::GetInstance()->Load("Button_Hover_" + ButtonId,btn->GetOnHoverImageSource());
}

void ButtonContainer::Show(std::string ButtonId){
    Button* btn = ButtonMap[ButtonId];
    SDL_Rect rect = {btn->XPos,btn->YPos,btn->Width,btn->Height};
    Image::GetInstance()->Show(btn->CurrentImage + ButtonId,rect);
    btn->CurrentImage = "Button_";
    btn->isClicked();
}

void Button::isClicked(){

    int MouseX,MouseY;
    Event::GetInstance()->GetMouseState(MouseX,MouseY);

    if(MouseX >= XPos && MouseX <= XPos + Width &&
        MouseY >= YPos && MouseY <= YPos + Height)
    {
        CurrentImage = "Button_Hover_";
        if(Event::GetInstance()->MouseButtonLeft()){
            if(OnClick != nullptr)
                OnClick();
        }
    }
}

void CreateButton(std::string ButtonId,Button* btn){
    ButtonContainer::GetInstance()->Create(ButtonId,btn);
}

Button* GetButton(std::string ButtonId){
    Button* btn = ButtonContainer::GetInstance()->GetButton(ButtonId);
    if(btn == nullptr){
        std::cout<<"ButtonId having Id "<<ButtonId<<" is not defined \n";
        exit(0);
    }
    return btn;
}
