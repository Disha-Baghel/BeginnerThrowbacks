#include <iostream>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_image.h>
#include "Game.h"

#define width 800
#define height 500

Game* Game::s_GameInstance;

Game* Game::instance()
{
    if(Game::s_GameInstance == NULL)
        s_GameInstance = new Game();
    return s_GameInstance;
}

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(width, height, 0, &m_Window, &m_Renderer);

	srand(time(NULL));

	m_Running = true;
	turn = 1;

	initTexture();	
};

void Game::initTexture()
{
	SDL_Surface* surfaceCircle = IMG_Load("circle.png");
	SDL_Surface* surfaceCorss = IMG_Load("cross.png");

	m_Circle = SDL_CreateTextureFromSurface(m_Renderer, surfaceCircle);
	m_Cross = SDL_CreateTextureFromSurface(m_Renderer, surfaceCorss);

	SDL_FreeSurface(surfaceCircle);
	SDL_FreeSurface(surfaceCorss);
}

int Game::checkForWin()
{
    static char possibleFormations[8][3][2] = {{{0,0},{0,1},{0,2} },  
	    			 {{1,0},{1,1},{1,2}},  
				 {{2,0},{2,1},{2,2}},

				 {{0,0},{1,0},{2,0}},
			       	 {{0,1},{1,1},{2,1}},  
				 {{0,2},{1,2},{2,2}},

                      		 {{0,0},{1,1},{2,2}}, 
				 {{0,2},{1,1},{2,0}}};

    for(int i=0 ; i<8 ; ++i)
    {
        int count1 = 0;
	int count2 = 0;

        for(int j=0;j<3;j++)
        {
            int n = m_Matrix[possibleFormations[i][j][0]][possibleFormations[i][j][1]];
            if(n == 1)
                ++count1;
            else if(n == 2)
                ++count2;

        }

        if(count1 == 3)
            return 1;

        else if(count2 == 3)
            return 2;
    }

    return 0;
}

void Game::eventHandler()
{
    if(SDL_PollEvent(&m_Event))
    {
        switch(m_Event.type)
        {
            case SDL_QUIT: m_Running = false;break;
            case SDL_MOUSEBUTTONDOWN:
                int x,y;
                SDL_GetMouseState(&x,&y);
                if(m_Event.button.button == SDL_BUTTON_LEFT)
                {
                    m_Matrix[(y-150)/50][(x-300)/50] = turn;
                    turn = (turn==1)?2:1;
                }
        }

    }
}

void Game::draw()
{
    SDL_SetRenderDrawColor(m_Renderer,255,255,255,255);
    SDL_RenderClear(m_Renderer);

    SDL_SetRenderDrawColor(m_Renderer,0,0,0,255);
    SDL_RenderDrawLine(m_Renderer,350,150,350,300);
    SDL_RenderDrawLine(m_Renderer,400,150,400,300);
    SDL_RenderDrawLine(m_Renderer,300,200,450,200);
    SDL_RenderDrawLine(m_Renderer,300,250,450,250);

    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    {
        if(m_Matrix[i][j] == 1 or m_Matrix[i][j] == 2)
        {
            SDL_Rect rect = {j*50 + 300 + j,i*50 + 150 + i,49,49};

            if(m_Matrix[i][j] == 1)
                SDL_RenderCopy(m_Renderer,m_Circle,NULL,&rect);
            else if(m_Matrix[i][j] == 2)
                SDL_RenderCopy(m_Renderer,m_Cross,NULL,&rect);
        }
    }

    SDL_RenderPresent(m_Renderer);
}

bool Game::loop()
{
    eventHandler();
    draw();

    int ret;
    if(ret = checkForWin())
    {
        std::cout<<ret<<" won";
        m_Running = false;
    }

    return m_Running;
}
