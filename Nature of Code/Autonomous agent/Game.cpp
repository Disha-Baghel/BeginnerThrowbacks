#include "Game.h"

Game::Game()
{
    CreateWindow(800,500);
    v = new Vehicle(100,250,10);
}

void Game::logic()
{
    v->seek({(float)mouseX,(float)mouseY});
    v->update();
}

void Game::draw()
{
    v->display();
}

void Game::onKeyClick()
{

}

void Game::onMouseClick()
{

}
