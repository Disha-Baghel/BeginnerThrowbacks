#include <iostream>
#include <iomanip>
#include <conio.h>

enum direction {up,down,left,right};

struct cublet
{
    char front,down,left,right,up,back;
};

class CUBE
{
    char cub_f[4];
    char cub_d[4];
    char cub_m_f[4];
    char cub_m_r[4];
    char cub_u_f[4];
    char cub_d_c_f[4];
    char cub_d_c_r[4];
    char cub_d_c_d[4];
    char cub_u_c_f[4];
    const char color[4] = {'r','b','o','g'};
    std::string answer;
private:
    void Refresh();
    void flip_cublet(direction d,cublet& c);
    void flip_upface(direction dir);
    void flip_cube(direction dir);
    void rotate(char c,direction dir);
    void rotate_clockwise(char c);
    void rotate_anti_clockwise(char c);
public:
    CUBE();
    void show_cube();
    void Set_cube();
    void make_white_cross();
    void solve_white_corners();
    void solve_mid_layer();
    void make_yellow_cross();
    void show_answer();
};
