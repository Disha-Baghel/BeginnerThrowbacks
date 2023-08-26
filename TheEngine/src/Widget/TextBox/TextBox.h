#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <string>

class TextBox{
    static TextBox* Instance;
public:
    static TextBox* GetInstance(){return Instance = (Instance != nullptr)?Instance:new TextBox;}
    void Show(std::string textbox);
};

#endif // TEXTBOX_H
