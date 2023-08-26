#include "functions.h"

int main()
{
    CUBE cube;
    cube.Set_cube();
    cube.make_white_cross();
    cube.solve_white_corners();
    cube.solve_mid_layer();
    cube.make_yellow_cross();
    cube.show_answer();

    return 0;
}
