#include "Page.h"
#include "Button.h"
#include "TextBox.h"
#include <iostream>
#include <fstream>

PageContainer* PageContainer::Instance = nullptr;

void Page::Add_Button(std::string BtnID){
    ButtonMap.push_back(BtnID);
}

void Page::Add_TextBox(std::string TextBoxID){
    TextBoxMap.push_back(TextBoxID);
}

void Page::Show(){
    for(std::string& btnID:ButtonMap){
        ButtonContainer::GetInstance()->Show(btnID);
    }
    for(std::string& textboxId:TextBoxMap){
        TextBox::GetInstance()->Show(textboxId);
    }
}

void CreatePage(std::string PageId,Page* p){
    PageContainer::GetInstance()->CreatePage(PageId,p);
}

Page* ActivePage;

void ActivatePage(std::string PageId){
    ActivePage = PageContainer::GetInstance()->GetPage(PageId);
}

Page* GetActivePage(){
    if(ActivePage == nullptr){
        std::cout<<"ActivePage undefined";
        exit(0);
    }
    return ActivePage;
}
