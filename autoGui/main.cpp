#include "autoGui.h"
#include <cmath>
#include <windows.h>

int main()
{
    autoGui::Time::WaitSecond(2);

    int d = 1;
    while(d != 100){
    autoGui::Mouse::dragRel(0,-d);
    autoGui::Mouse::dragRel(d,0);
    autoGui::Mouse::dragRel(0,d);
    autoGui::Mouse::dragRel(-d,0);
    autoGui::Time::WaitMilli(100);
    d+=10;
    }
	return 0;
}
