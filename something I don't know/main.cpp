#include "turtle.h"

int main(int argc,char** argv)
{
    turtle turt;

    turt.pos(400,250);

    int k = 0;

    while(1)
    {
        turt.curve(k);
        turt.reset();
        k++;
    }

    return 0;
}
