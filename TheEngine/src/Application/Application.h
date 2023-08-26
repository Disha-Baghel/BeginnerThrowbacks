#ifndef APPLICATION_H
#define APPLICATION_H

#include "Engine.h"

class Application: public Engine{
    Application();
    void Draw();
    static Application* Instance;
public:
    static Application* GetInstance(){return Instance = (Instance != nullptr)?Instance: new Application();}
};

#endif // APPLICATION_H
