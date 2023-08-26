#ifndef CANVAS_H
#define CANVAS_H

#include "../Window/Window.h"
#include "../OpenGL/OpenGL.h"

class Canvas: public Window,public OpenGL
{
    bool EnableGL;
    static int CanvasCount;
    bool StaticCanvas;

    bool prevKeyboardState[256] = {0};
public:
    Canvas(UINT width = 640,UINT height = 480,bool GL = true);
    int Run();
protected:
    virtual void Update(){};
    virtual void Render()    = 0;

    void noLoop(){StaticCanvas = true;}
    bool KeyDown(int key);
    bool KeyIsDown(int key);

    UINT WIDTH,HEIGHT;
    UINT MouseX,MouseY;
    BYTE KeyCode;
private:
    void ShowCanvas();
    LRESULT HandleMessage(UINT uMsg,WPARAM wParam,LPARAM lParam);
};

#endif // CANVAS_H
