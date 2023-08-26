#include "Engine.h"

class Cell
{
    int x,y;
    float w;
public:
    bool state;
    bool previous;
    Cell(int x=0,int y=0,int w=0)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        previous = 0;
    }
    void display()
    {
        if(previous == 0 && state == 1)
            Engine::FillRect({x*w,y*w,w,w,},{0,0,255});
        else if(state == 1)
            Engine::FillRect({x*w,y*w,w,w,},{0,0,0});
        else if(previous == 1 && state == 0)
            Engine::FillRect({x*w,y*w,w,w,},{255});
        else
            Engine::FillRect({x*w,y*w,w,w,});
    }
};
