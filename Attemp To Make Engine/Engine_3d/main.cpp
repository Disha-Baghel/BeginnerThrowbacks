#include "Engine_3d.h"

object obj("cube.obj");
object obj2("Object/rabbit.obj");
void draw();

int main(int argc,char** argv)
{
    Engine_3d engine;

    vec3d pos = {0,0,3};
    obj.set_position(pos);
    pos = {0,0,0.3};
    obj2.set_position(pos);

    engine.Start(draw);
    return 0;
}

void draw()
{
    obj.draw();
    obj.Rotate('x',0.01);
    obj2.draw();
    obj2.Rotate('x',0.01);
}
