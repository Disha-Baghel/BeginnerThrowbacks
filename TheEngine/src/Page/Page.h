#ifndef PAGE_H
#define PAGE_H

#include <string>
#include <vector>
#include <map>

class Page
{
    std::vector<std::string> ButtonMap;
    std::vector<std::string> TextBoxMap;
public:
    Page(Data* data){}
    void Add_Button(std::string BtnID);
    void Add_TextBox(std::string TextBoxID);
    void Show();
};

class PageContainer{
    std::map<std::string,Page*> PageMap;
    static PageContainer* Instance;
public:
    static PageContainer* GetInstance(){return Instance = (Instance != nullptr)?Instance:new PageContainer;}
    void CreatePage(std::string PageId,Page* p){
        PageMap[PageId] = p;
    }
    Page* GetPage(std::string PageId){
        return PageMap[PageId];
    }
};

void ActivatePage(std::string PageId);
Page* GetActivePage();
void CreatePage(std::string PageId,Page* p);

#endif // PAGE_H
