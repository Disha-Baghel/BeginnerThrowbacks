#include "Engine2d.h"

int main(int argc,char** argv) {

    Engine2d::GetInstance()->Start();
    Engine2d::GetInstance()->Clear();

    return 0;
}
