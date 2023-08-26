#include "Engine.h"

/*
    TODO:
    Put each files in their respective folders
    Main folder will be Engine
    Make Some Changes to Class Names in files
*/

/**
    IF POSSIBLE, MAKE A COMPLETELY NEW PROJECT
*/

class Application: public GLApp
{
    void Setup() override
    {
        CreateCanvas(800,500);
        SetAppName("Hello");
    }
    void Update(float dt) override
    {

    }
    void Render() override
    {
        glTranslatef(0.0,0.0,-3.0f);
        DrawLine(0,0,0,1,1,0);
    }
};

int main()
{
    Application app;
    return app.Run();
}
