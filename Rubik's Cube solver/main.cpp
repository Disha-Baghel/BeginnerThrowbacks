#include "Display.h"
#include "Cube/Box.h"

int main(int argc,char** argv)
{
    Display display(640,480);

    Box box(1.0f);

    Camera camera(glm::vec3(0.0f,0.0f,3.0f),45, 640.0/480.0, 0.1f, 1000.0f);

    while(!display.isClosed())
    {
        display.Clear();

        box.Draw(camera);

        display.Update();
        camera.Update();
    }

    return 0;
}
