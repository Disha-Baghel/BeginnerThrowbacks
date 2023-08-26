#include "Engine.h"

#ifdef main
#undef main
#endif // main

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{

    return Engine_main();
}
