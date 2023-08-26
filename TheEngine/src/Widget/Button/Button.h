#ifndef BUTTON_H
#define BUTTON_H

#include <map>

class Button{
public:
    int XPos,YPos,Width,Height;
    std::string Text;
    std::string ImageSource;
    std::string OnHoverImageSource;
    std::string CurrentImage;
    Button(std::string ButtonId);
    Button(int x,int y,int w,int h,std::string Txt,std::string ImgSrc = "MY PHOTO.png",std::string OnHoverImgSrc = "OnHover MY PHOTO.png"){
        XPos = x;
        YPos = y;
        Width = w;
        Height = h;
        Text = Txt;
        ImageSource = ImgSrc;
        OnHoverImageSource = OnHoverImgSrc;
    }
    std::string GetImageSource(){return ImageSource;}
    std::string GetOnHoverImageSource(){return OnHoverImageSource;}
    void isClicked();
    void SetOnClickListener(void (*onClick)()){this->OnClick = onClick;}
    void (*OnClick)(){};
};

class ButtonContainer{
    std::map<std::string,Button*> ButtonMap;
    static ButtonContainer* Instance;
public:
    static ButtonContainer* GetInstance(){return Instance = (Instance != nullptr)?Instance:new ButtonContainer();}
    void Create(std::string ButtonId,Button* btn);
    void Show(std::string BtnId);
    Button* GetButton(std::string ButtonId){return ButtonMap[ButtonId];}
};

void CreateButton(std::string ButtonId,Button* btn);
Button* GetButton(std::string ButtonId);

#endif // BUTTON_H
