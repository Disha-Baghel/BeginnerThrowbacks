#include "Application.h"

int main(int argc,char** argv)
{
    while(Application::Instance()->loop());

    return 0;
}
