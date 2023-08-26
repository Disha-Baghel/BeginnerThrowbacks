#include "functions.h"
#include <SDL2/SDL.h>
#include <sstream>
#include <vector>

cublet cube[3][3][3];

CUBE::CUBE()
{
    cube[2][2][0] = {  0,  0, 'g',  0, 'w', 'o'};
    cube[2][2][1] = {  0,  0,  0,  0, 'w', 'o'};
    cube[2][2][2] = {  0,  0,  0, 'b', 'w', 'o'};
    cube[1][2][0] = {  0,  0, 'g',  0, 'w',  0 };
    cube[1][2][1] = {  0,  0,  0,  0, 'w',  0 };
    cube[1][2][2] = {  0,  0,  0, 'b', 'w',  0 };
    cube[0][2][0] = { 'r',  0, 'g',  0, 'w',  0 };
    cube[0][2][1] = { 'r',  0,  0,  0, 'w',  0 };
    cube[0][2][2] = { 'r',  0,  0, 'b', 'w',  0 };
    cube[2][1][0] = {  0,  0, 'g',  0,  0, 'o'};
    cube[2][1][1] = {  0,  0,  0,  0,  0, 'o'};
    cube[2][1][2] = {  0,  0,  0, 'b',  0, 'o'};
    cube[1][1][0] = {  0,  0, 'g',  0,  0,  0 };
    cube[1][1][1] = {  0,  0,  0,  0,  0,  0 };
    cube[1][1][2] = {  0,  0,  0, 'b',  0,  0 };
    cube[0][1][0] = { 'r',  0, 'g',  0,  0,  0 };
    cube[0][1][1] = { 'r',  0,  0,  0,  0,  0 };
    cube[0][1][2] = { 'r',  0,  0, 'b',  0,  0 };
    cube[2][0][0] = {  0, 'y', 'g',  0,  0, 'o'};
    cube[2][0][1] = {  0, 'y',  0,  0,  0, 'o'};
    cube[2][0][2] = {  0, 'y',  0, 'b',  0, 'o'};
    cube[1][0][0] = {  0, 'y', 'g',  0,  0,  0 };
    cube[1][0][1] = {  0, 'y',  0,  0,  0,  0 };
    cube[1][0][2] = {  0, 'y',  0, 'b',  0,  0 };
    cube[0][0][0] = { 'r', 'y', 'g',  0,  0,  0 };
    cube[0][0][1] = { 'r', 'y',  0,  0,  0,  0 };
    cube[0][0][2] = { 'r', 'y',  0, 'b',  0,  0 };
}

void CUBE::show_cube()
{
    for(int i=2; i>=0; i--)
        std::cout<<std::setw(25)<<cube[2][i][0].back<<'\t'<<cube[2][i][1].back<<'\t'<<cube[2][i][2].back<<'\n';

    std::cout<<'\n';

    for(int i=2; i>=0; i--)
    {
        std::cout<<cube[i][2][0].left<<'\t'<<cube[i][1][0].left<<'\t'<<cube[i][0][0].left<<'\t';
        std::cout<<cube[i][0][0].down<<'\t'<<cube[i][0][1].down<<'\t'<<cube[i][0][2].down<<'\t';
        std::cout<<cube[i][0][2].right<<'\t'<<cube[i][1][2].right<<'\t'<<cube[i][2][2].right<<'\t';
        std::cout<<cube[i][2][0].up<<'\t'<<cube[i][2][1].up<<'\t'<<cube[i][2][2].up<<'\t';

        if(i != 0 )
            std::cout<<'\n';
    }

    std::cout<<"\n\n";

    for(int i=0; i<3; i++)
        std::cout<<std::setw(25)<<cube[0][i][0].front<<'\t'<<cube[0][i][1].front<<'\t'<<cube[0][i][2].front<<'\n';
}

void CUBE::Set_cube()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_CreateWindowAndRenderer(400,500,0,&window,&renderer);
    bool done = false;
    SDL_Event event;

    struct Plate
    {
        SDL_Rect rect;
        SDL_Color col;
        char clr = 0;
    } plate[6][9];

    while(!done)
    {
        if(SDL_PollEvent(&event))
        {
            SDL_Color col;
            char ch;
            switch(event.type)
            {
            case SDL_QUIT:
                done = true;
                break;
            case SDL_KEYDOWN:
                ch = event.key.keysym.sym;
                switch(event.key.keysym.sym)
                {
                case 'r':
                    col = {255,0,0,255};
                    break;
                case 'g':
                    col = {0,255,0,255};
                    break;
                case 'b':
                    col = {0,0,255,255};
                    break;
                case 'y':
                    col = {255,255,0,255};
                    break;
                case 'o':
                    col = {255,128,0,255};
                    break;
                case 'w':
                    col = {255,255,255,255};
                    break;
                case SDLK_RETURN:
                    done = true;
                    break;
                }

                break;
            case SDL_MOUSEBUTTONDOWN:
                /*system("cls");
                show_cube();*/
                switch(event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    int x,y;
                    SDL_GetMouseState(&x,&y);

                    plate[x/55][y/55].col = col;
                    plate[x/55][y/55].clr = ch;

                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,255,255,255);

        for(int i=0; i<9; i++)
            for(int j=0; j<6; j++)
            {
                plate[j][i].rect = {j*55,i*55,50,50};
            }

        plate[1][1].col = {255,255,255,255};
        plate[1][1].clr = 'w';
        plate[4][1].col = {255,0,0,255};
        plate[4][1].clr = 'r';
        plate[1][4].col = {0,255,0,255};
        plate[1][4].clr = 'g';
        plate[4][4].col = {255,255,0,255};
        plate[4][4].clr = 'y';
        plate[1][7].col = {0,0,255,255};
        plate[1][7].clr = 'b';
        plate[4][7].col = {255,128,0,255};
        plate[4][7].clr = 'o';

        for(int i=0; i<9; i++)
            for(int j=0; j<6; j++)
            {
                SDL_SetRenderDrawColor(renderer,plate[j][i].col.r,plate[j][i].col.g,plate[j][i].col.b,255);
                SDL_RenderFillRect(renderer,&plate[j][i].rect);
            }

        for(int i=2; i>=0; i--)
            for(int j=0; j<3; j++)
            {
                cube[i][2][j].up = plate[j][2-i].clr;
                cube[0][i][j].front = plate[3+j][2-i].clr;
                cube[2-j][i][0].left = plate[j][3+2-i].clr;
                cube[2-i][0][j].down = plate[3+j][3+2-i].clr;
                cube[j][i][2].right = plate[j][6+2-i].clr;
                cube[2][i][2-j].back = plate[3+j][6+2-i].clr;
            }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void CUBE::flip_cublet(direction d,cublet& c)
{
    cublet temp;

    switch(d)
    {
    case up:
        temp = {c.down,c.back,c.left,c.right,c.front,c.up};
        break;
    case down:
        temp = {c.up,c.front,c.left,c.right,c.back,c.down};
        break;
    case left:
        temp = {c.right,c.down,c.front,c.back,c.up,c.left};
        break;
    case right:
        temp = {c.left,c.down,c.back,c.front,c.up,c.right};
        break;
    }

    c = temp;
}

void CUBE::flip_upface(direction dir)
{
    int index = 0;
    cublet cblt[8];

    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
            if(i == 1 && j == 1)
                continue;

            if(dir == left)
                cblt[index] = cube[j][2][i];
            else if(dir == right)
                cblt[index] = cube[2-j][2][2-i];
            index++;
        }

    for(int i=0; i<8; i++)
    {
        flip_cublet(dir,cblt[i]);
    }

    index = 0;

    for(int i=2; i>=0; i--)
        for(int j=0; j<3; j++)
        {
            if(i == 1 && j == 1)
                continue;

            cube[i][2][j] = cblt[index];

            index++;
        }
}

void CUBE::flip_cube(direction dir)
{
    int index = 0;
    cublet cblt[26];

    for(int j=2; j>=0; j--)
        for(int k=2; k>=0; k--)
            for(int i=2; i>=0; i--)
            {
                if(i == 1 && j == 1 && k == 1)
                    continue;

                if(dir == right)
                    cblt[index] = cube[i][j][k];
                else if(dir == left)
                    cblt[index] = cube[2-i][j][2-k];
                else if(dir == up)
                    cblt[index] = cube[2-j][k][2-i];
                else if(dir == down)
                    cblt[index] = cube[j][2-k][2-i];
                index++;
            }

    for(int i=0; i<26; i++)
    {
        if(dir == right)
            flip_cublet(right,cblt[i]);
        else if(dir == left)
            flip_cublet(left,cblt[i]);
        else if(dir == up)
            flip_cublet(up,cblt[i]);
        else if(dir == down)
            flip_cublet(down,cblt[i]);
    }

    index = 0;

    for(int j=2; j>=0; j--)
        for(int i=2; i>=0; i--)
            for(int k=0; k<3; k++)
            {
                if(i == 1 && j == 1 && k == 1)
                    continue;

                cube[i][j][k] = cblt[index];
                index++;
            }
}

void CUBE::rotate(char c,direction dir)
{
    std::string clr;

    switch(c)
    {
    case 'w':
        clr = "White ";
        flip_upface(dir);
        break;
    case 'r':
        clr = "Red ";
        flip_cube(up);
        flip_upface(dir);
        flip_cube(down);
        break;
    case 'b':
        clr = "Blue ";
        flip_cube(left);
        flip_cube(up);
        flip_upface(dir);
        flip_cube(down);
        flip_cube(right);
        break;
    case 'g':
        clr = "Green ";
        flip_cube(right);
        flip_cube(up);
        flip_upface(dir);
        flip_cube(down);
        flip_cube(left);
        break;
    case 'o':
        clr = "Orange ";
        flip_cube(down);
        flip_upface(dir);
        flip_cube(up);
        break;
    case 'y':
        clr = "Yellow ";
        flip_cube(up);
        flip_cube(up);
        flip_upface(dir);
        flip_cube(down);
        flip_cube(down);
        break;
    }

    switch(dir)
    {
    case left:
        answer += clr;
        std::cout<<clr<<'\n';
        break;
    case right:
        answer += "Anti_" + clr;
        std::cout<<"Anti_"<<clr<<'\n';
        break;
    default:
        break;
    }

    getch();
}

void CUBE::rotate_clockwise(char c)
{
    rotate(c,left);
}

void CUBE::rotate_anti_clockwise(char c)
{
    rotate(c,right);
}

void CUBE::Refresh()
{
    char CUB_F[4] = {cube[0][0][1].front,cube[1][0][2].right,cube[2][0][1].back,cube[1][0][0].left};
    char CUB_D[4] = {cube[0][0][1].down,cube[1][0][2].down,cube[2][0][1].down,cube[1][0][0].down};
    char CUB_M_F[4] = {cube[0][1][2].front,cube[2][1][2].right,cube[2][1][0].back,cube[0][1][0].left};
    char CUB_M_R[4] = {cube[0][1][2].right,cube[2][1][2].back,cube[2][1][0].left,cube[0][1][0].front};
    char CUB_U_F[4] = {cube[0][2][1].front,cube[1][2][2].right,cube[2][2][1].back,cube[1][2][0].left};
    char CUB_D_C_F[4] = {cube[0][0][2].front,cube[2][0][2].right,cube[2][0][0].back,cube[0][0][0].left};
    char CUB_D_C_R[4] = {cube[0][0][2].right,cube[2][0][2].back,cube[2][0][0].left,cube[0][0][0].front};
    char CUB_D_C_D[4] = {cube[0][0][2].down,cube[2][0][2].down,cube[2][0][0].down,cube[0][0][0].down};
    char CUB_U_C_F[4] = {cube[0][2][2].front,cube[2][2][2].right,cube[2][2][0].back,cube[0][2][0].front};

    for(int i=0;i<4;i++)
    {
        cub_f[i] = CUB_F[i];
        cub_d[i] = CUB_D[i];
        cub_m_f[i] = CUB_M_F[i];
        cub_m_r[i] = CUB_M_R[i];
        cub_u_f[i] = CUB_U_F[i];
        cub_d_c_f[i] = CUB_D_C_F[i];
        cub_d_c_r[i] = CUB_D_C_R[i];
        cub_d_c_d[i] = CUB_D_C_D[i];
        cub_u_c_f[i] = CUB_U_C_F[i];
    }
}

void CUBE::show_answer()
{
    std::vector<std::string> ANSWER;

    std::stringstream ss(answer);
    int count = 1;
    while(ss>>answer)
    {
        ANSWER.push_back(answer);

        if(ANSWER[ANSWER.size()-1] == ("Anti_" + ANSWER[ANSWER.size() - 2]) ||
           ANSWER[ANSWER.size()-2] == ("Anti_" + ANSWER[ANSWER.size() - 1]))
        {
            ANSWER.pop_back();
            ANSWER.pop_back();
        }
        else if(ANSWER[ANSWER.size() - 1] == ANSWER[ANSWER.size() - 2])
            count++;
        else
        {
            if(count == 3)
            {
                ANSWER.pop_back();
                ANSWER.pop_back();
                ANSWER.pop_back();
                ANSWER[ANSWER.size() - 1] = "Anti_" + ANSWER[ANSWER.size() - 1];
                ANSWER.push_back(answer);
            }
            else if(count == 4)
            {
                ANSWER.pop_back();
                ANSWER.pop_back();
                ANSWER.pop_back();
                ANSWER.pop_back();
                ANSWER.pop_back();
                ANSWER.push_back(answer);
            }

            count = 0;
        }
    }

    for(unsigned int i=0;i<ANSWER.size();i++)
        std::cout<<ANSWER[i]<<'\n';
}

void CUBE::make_white_cross()
{
    int i=0;

    Refresh();

    while(cube[1][2][0].up != 'w' || cube[0][2][1].up != 'w' || cube[1][2][2].up != 'w' || cube[2][2][1].up != 'w')
    {
        if(cub_d[i] == 'w')
        {
            if(cub_f[i] == color[i])
            {
                rotate_clockwise(color[i]);
                rotate_clockwise(color[i]);
                i = -1;
            }
            else
                rotate_clockwise('y');
        }
        else if(cub_f[i] == 'w')
        {
            if(cub_d[i] == color[i])
            {
                rotate_clockwise('y');
                rotate_clockwise(color[(i+1)%4]);
                rotate_anti_clockwise(color[i]);
                rotate_anti_clockwise(color[(i+1)%4]);
                rotate_anti_clockwise('y');
                i = -1;
            }
            else
                rotate_clockwise('y');
        }
        else if(cub_m_r[i] == 'w')
        {
            rotate_clockwise(color[i]);
            rotate_clockwise('y');
            rotate_anti_clockwise(color[i]);
            i = -1;
        }
        else if(cub_m_f[i] == 'w')
        {
            rotate_anti_clockwise(color[(i+1)%4]);
            rotate_clockwise('y');
            rotate_clockwise(color[(i+1)%4]);
            i = -1;
        }
        else if(cub_u_f[i] == 'w')
        {
            rotate_clockwise(color[i]);
            rotate_clockwise(color[i]);
            i = -1;
        }

        i++;
        if(i==4)
            i=0;

        Refresh();
    }
}

void CUBE::solve_white_corners()
{
    int i=0;

    Refresh();

    while(cube[0][2][2].up != 'w' || cube[2][2][2].up != 'w' || cube[2][2][0].up != 'w' || cube[0][2][0].up != 'w')
    {
        if(cub_d_c_f[i] == 'w')
        {
            if(cub_d_c_r[i] == color[(i+1)%4] && cub_d_c_d[i] == color[i])
            {
                rotate_anti_clockwise('y');
                rotate_anti_clockwise(color[i+1]);
                rotate_clockwise('y');
                rotate_clockwise(color[i+1]);
                i = -1;
            }
            else
                rotate_clockwise('y');
        }
        else if(cub_d_c_r[i] == 'w')
        {
            if(cub_d_c_d[i] == color[(i+1)%4] && cub_d_c_f[i] == color[i])
            {
                rotate_clockwise('y');
                rotate_clockwise(color[i]);
                rotate_anti_clockwise('y');
                rotate_anti_clockwise(color[i]);
                i = -1;
            }
            else
                rotate_clockwise('y');
        }
        else if(cub_d_c_d[i] == 'w')
        {
            if(cub_d_c_r[i] == color[i] && cub_d_c_f[i] == color[(i+1)%4])
            {
                rotate_anti_clockwise(color[(i+1)%4]);
                rotate_clockwise('y');
                rotate_clockwise(color[(i+1)%4]);
                rotate_clockwise(color[i]);
                rotate_clockwise('y');
                rotate_clockwise('y');
                rotate_anti_clockwise(color[i]);
                i = -1;
            }
            else
                rotate_clockwise('y');
        }
        else if(cub_u_c_f[i] == 'w')
        {
            rotate_anti_clockwise(color[(i+1)%4]);
            rotate_clockwise('y');
            rotate_clockwise(color[(i+4)%4]);
        }

        i++;
        if(i==4)
            i=0;

        Refresh();
    }
}

void CUBE::solve_mid_layer()
{
    int i = 0;

    Refresh();

    while(cube[0][1][2].front != 'r' || cube[0][1][2].right != 'b' || cube[2][1][2].right != 'b' || cube[2][1][2].back != 'o'
          || cube[2][1][0].back != 'o' || cube[2][1][0].left != 'g' || cube[0][1][0].left != 'g' || cube[0][1][0].front != 'r')
    {
        if(cub_f[i] != 'y' && cub_d[i] != 'y')
        {
            if(cub_f[i] == color[i])
            {
                if(cub_d[i] == color[(i+1)%4])
                {
                    rotate_anti_clockwise('y');
                    rotate_anti_clockwise(color[(i+1)%4]);
                    rotate_clockwise('y');
                    rotate_clockwise(color[(i+1)%4]);
                    rotate_clockwise('y');
                    rotate_clockwise(color[i]);
                    rotate_anti_clockwise('y');
                    rotate_anti_clockwise(color[i]);
                    i = -1;
                }
                if(cub_d[i] == color[(i+3)%4])
                {
                    rotate_clockwise('y');
                    rotate_clockwise(color[(i+3)%4]);
                    rotate_anti_clockwise('y');
                    rotate_anti_clockwise(color[(i+3)%4]);
                    rotate_anti_clockwise('y');
                    rotate_anti_clockwise(color[i]);
                    rotate_clockwise('y');
                    rotate_clockwise(color[i]);
                    i = -1;
                }
            }
            else
                rotate_clockwise('y');
        }
        else if((cub_m_f[i] != color[i] || cub_m_r[i] != color[(i+1)%4]) && (cub_m_f[i] != 'y' || cub_m_r[i] != 'y') )
        {
            rotate_anti_clockwise('y');
            rotate_anti_clockwise(color[(i+1)%4]);
            rotate_clockwise('y');
            rotate_clockwise(color[(i+1)%4]);
            rotate_clockwise('y');
            rotate_clockwise(color[i]);
            rotate_anti_clockwise('y');
            rotate_anti_clockwise(color[i]);
            i = -1;
        }
        else
            rotate_clockwise('y');

        i++;
        if(i == 4)
            i = 0;

        Refresh();
    }
}

void CUBE::make_yellow_cross()
{
    Refresh();

    while(cub_d[0] != 'y' || cub_d[1] != 'y' || cub_d[2] != 'y' || cub_d[3] != 'y')
    {
        if((cub_d[1] == 'y' && cub_d[3] == 'y') || (cub_d[1] == 'y' && cub_d[2] == 'y') || (cub_d[0] != 'y' && cub_d[1] != 'y' && cub_d[2] != 'y' && cub_d[3] != 'y'))
        {
            rotate_clockwise('r');
            rotate_clockwise('g');
            rotate_clockwise('y');
            rotate_anti_clockwise('g');
            rotate_anti_clockwise('y');
            rotate_anti_clockwise('r');
        }
        else
            rotate_clockwise('y');

        Refresh();
    }
}
