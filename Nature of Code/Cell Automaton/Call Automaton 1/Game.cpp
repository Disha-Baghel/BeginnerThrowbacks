#include "Game.h"
#include <iostream>
#include <stdlib.h>

Game::Game()
{
    CreateWindow(800,500);

    for(int i=0;i<500;i++)
    {
        for(int j=0;j<800;j++)
            board[i][j] = rand() % 2;
    }

    next = new bool*[500];
    for(int i=0;i<800;i++)
        next[i] = new bool[800];
}

void Game::logic()
{
    for(int y=1;y<500-1;y++)
    {
        for(int x=1;x<800-1;x++)
        {
            int neighbors = 0;

            for(int i=-1;i<=1;i++)
                for(int j=-1;j<=1;j++)
                    neighbors += board[y+i][x+j];
            neighbors -= board[y][x];

            if ((board[y][x] == 1) && (neighbors < 2)) next[y][x] = 0;
            else if ((board[y][x] == 1) && (neighbors > 3)) next[y][x] = 0;
            else if ((board[y][x] == 0) && (neighbors == 3)) next[y][x] = 1;
            else next[y][x] = board[y][x];
        }
    }

    for(int i=0;i<500;i++)
    {
        for(int j=0;j<800;j++)
            board[i][j] = next[i][j];
    }
}

void Game::draw()
{
    for(int i=0;i<500;i++)
    {
        for(int j=0;j<800;j++)
        {
            if(board[i][j] == 1)
                Engine::DrawPoint(j,i,{0,255,0});
        }
    }
}

void Game::onKeyClick()
{

}

void Game::onMouseClick()
{

}
