#ifndef HOME_H
#define HOME_H

#include "Page.h"
#include "Button.h"

void Home(){
    Parse Data= Parse("res/Xml/Home.xml");
    CreatePage("Home",Page(Data));
    Button* btn = GetButton("ok");

    btn->SetOnClickListener([](){

        ActivatePage("Other");

    });
}

#endif // HOME_H
