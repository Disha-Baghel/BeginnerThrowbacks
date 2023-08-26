#include "Game.h"
#include <iostream>
#include <stdlib.h>

Game::Game()
{
    CreateWindow(800,500);

    board = new Cell*[50];
    for(int i=0;i<80;i++)
        board[i] = new Cell[80];

    for(int i=0;i<50;i++)
    {
        for(int j=0;j<80;j++)
        {
            Cell c(j,i,10);
            board[i][j] = c;
        }
    }

    next = new Cell*[50];
    for(int i=0;i<80;i++)
        next[i] = new Cell[80];

    for(int i=0;i<50;i++)
    {
        for(int j=0;j<80;j++)
        {
            next[i][j] = board[i][j];
            board[i][j].state = rand() % 2;
        }
    }
}

void Game::logic()
{
    for(int y=1;y<50-1;y++)
    {
        for(int x=1;x<80-1;x++)
        {
            int neighbors = 0;

            for(int i=-1;i<=1;i++)
                for(int j=-1;j<=1;j++)
                    neighbors += board[y+i][x+j].state;
            neighbors -= board[y][x].state;

            if ((board[y][x].state == 1) && (neighbors < 2)) next[y][x].state = 0;
            else if ((board[y][x].state == 1) && (neighbors > 3)) next[y][x].state = 0;
            else if ((board[y][x].state == 0) && (neighbors == 3)) next[y][x].state = 1;
            else next[y][x].state = board[y][x].state;
        }
    }

    for(int i=0;i<50;i++)
    {
        for(int j=0;j<80;j++)
            board[i][j] = next[i][j];
    }
}

void Game::draw()
{
    for(int i=0;i<50;i++)
    {
        for(int j=0;j<80;j++)
        {
            if(board[i][j].state == 1)
                board[i][j].display();
        }
    }
}

void Game::onKeyClick()
{

}

void Game::onMouseClick()
{

}
