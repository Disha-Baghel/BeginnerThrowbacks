#include <windows.h>
#include "Simplemain.h"

#ifdef main
#undef main
#endif // main

int APIENTRY WinMain(HINSTANCE  hInstance,
                     HINSTANCE  hPrevInstance,
                     LPSTR      lpCmdLine,
                     int        nCmdShow)
{
    return Simplemain();
}
