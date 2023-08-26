#include "Game.h"
#include <stdlib.h>

Game::Game()
{
    CreateWindow(800,500);
    for(int i=0;i<800;i++){
        for(int j=0;j<500;j++){
            c[i][j] = new cell(i,j);
        }
    }

    c[0][0]->alive = true;
}

void Game::logic()
{
    for(int i=1;i<800-1;i++){
        for(int j=1;j<500-1;j++){
            if(c[i-1][j-1]->alive){
                c[i][j]->alive = (c[i][j]->alive)?false:true;
            }
            if(c[i+1][j-1]->alive){
                c[i][j]->alive = (c[i][j]->alive)?false:true;
            }
            if(c[i-1][j]->alive){
                c[i][j]->alive = (c[i][j]->alive)?false:true;
            }
        }
    }
}

void Game::draw()
{
    for(int i=0;i<800;i++){
        for(int j=0;j<500;j++){
            if(c[i][j]->alive){
                DrawPoint(i,j);
            }
        }
    }
}

void Game::onKeyClick()
{

}

void Game::onMouseClick()
{

}
