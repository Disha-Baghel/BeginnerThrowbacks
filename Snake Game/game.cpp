#include "game.h"
#include <stdlib.h>
#include <ctime>

#define width 800
#define height 500
#define face_size 20

game::game()
{
    xFace = yFace = 100;
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    font = TTF_OpenFont("sans.ttf",24);

    SDL_CreateWindowAndRenderer(width,height,SDL_WINDOW_RESIZABLE,&window,&renderer);
    SDL_SetWindowTitle(window,"Snake");

    run = true;
    gameover = true;
    dir = stop;
    prevtime = SDL_GetTicks();
    score=0;
    ntail = 2;    // without setting ntail = 2, snake size doesn't increase before it's already eaten up two or three fruits
    lives = 3;

    srand(time(0));
    xFood = face_size*(rand() % (width/face_size));
    yFood = face_size*(rand() % (height/face_size));
}

void game::EventListener()
{
    prev_dir = dir;

    SDL_Event event;
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            run = false;
            break;
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_UP:
                if(prev_dir != down)
                {
                    dir = up;
                }
                break;
            case SDLK_DOWN:
                if(prev_dir != up)
                {
                    dir = down;
                }
                break;
            case SDLK_LEFT:
                if(prev_dir != right)
                {
                    dir = left;
                }
                break;
            case SDLK_RIGHT:
                if(prev_dir != left)
                {
                    dir = right;
                }
                break;
            }
        }
        break;
        }
    }
}

void game::update()
{
    Uint32 newtime = SDL_GetTicks()/75;
    Uint32 delta = newtime - prevtime;
    prevtime = newtime;

    int speed = delta*face_size;

    switch(dir)
    {
    case up:
        yFace-=speed;
        break;
    case down:
        yFace+=speed;
        break;
    case left:
        xFace-=speed;
        break;
    case right:
        xFace+=speed;
        break;
    case stop:
        break;
    }

    if(SDL_HasIntersection(&snake_face,&foodRect))
    {
        srand(time(0));
        xFood = face_size*(rand() % (width/face_size));
        yFood = face_size*(rand() % (height/face_size));
        score++;
        ntail++;
    }


    for(int i=2; i<ntail; i++)
    {
        if(xFace == tailX[i] && yFace == tailY[i])
        {
            yFace = 0;
            lives--;
            dir = down;
            for(int i=1; i<ntail; i++)
                tailY[i] = 0;           // only to hide snake's tail off the screen when it hits it's tail
            break;
        }
    }
}

void game::logic()
{
    if(xFace < 0)
        xFace = width - face_size;
    if(xFace + face_size > width)
        xFace = 0;
    if(yFace < 0)
        yFace = height - face_size;
    if(yFace + face_size> height)
        yFace = 0;

    tailX[0]=xFace;
    tailY[0]=yFace;
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X,prev2Y;
    for(int i=1; i<ntail; i++)
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }

    int pTime = SDL_GetTicks();
    if(lives < 1)
    {
        int time = SDL_GetTicks() - pTime;
        SDL_Event event;
        while(time<=7000)
        {
            time = SDL_GetTicks() - pTime;
            if(SDL_PollEvent(&event))
            {
                if(event.type == SDL_KEYDOWN)
                {
                    if(event.key.keysym.sym == SDLK_RETURN)
                    {
                        run = false;
                        break;
                    }
                }

                else if(event.type == SDL_QUIT)
                {
                    run = false;
                    break;
                }
            }

            SDL_SetRenderDrawColor(renderer,160,140,180,255);
            SDL_RenderClear(renderer);

            SDL_Rect quit_rect = {200,200,250,75};
            renderText("Press Enter to Quit Before " + std::to_string(7 - (time/1000)) + " seconds",quit_rect);

            SDL_RenderPresent(renderer);
        }

        lives = 3;
        ntail = 2;
        score = 0;
    }
}

void game::snake_tail()
{
    for(int i=0; i<ntail; i++)
    {
        tailRect = {tailX[i],tailY[i],face_size,face_size};
        SDL_RenderFillRect(renderer,&tailRect);
    }
}

void game::snake()
{
    snake_face = {xFace,yFace,face_size,face_size};
    SDL_RenderFillRect(renderer,&snake_face);

}

void game::food()
{
    SDL_SetRenderDrawColor(renderer,255,127,64,255);
    foodRect = {xFood,yFood,face_size,face_size};
    SDL_RenderFillRect(renderer,&foodRect);
}

float game::xPos(int y,int x1,int x2, int y1,int y2)
{
    float x = ((y-y1) * ((float)(x2 - x1) / (y2 - y1))) + x1;
    return x;
}

float game::yPos(int x,int x1,int x2, int y1,int y2)
{
    float y = (((float)(y2-y1)/(x2-x1)) * (x-x1)) + y1;
    return y;
}

void game::PositionLogic(int x,int y)
{
    if(x>400 && y > yPos(x,800,400,0,250) && y < yPos(x,400,800,250,500))
        SDL_SetRenderDrawColor(renderer,255,255,0,255);

    else if(x<400 && y > yPos(x,0,400,0,250) && y< yPos(x,400,0,250,500))
        SDL_SetRenderDrawColor(renderer,0,255,255,255);

    else if(y<250 && x > xPos(y,0,400,0,250) && x < xPos(y,800,400,0,250))
        SDL_SetRenderDrawColor(renderer,255,0,255,255);

    else if(y>250 && x > xPos(y,0,400,500,250) && x < xPos(y,800,400,500,250))
        SDL_SetRenderDrawColor(renderer,0,255,0,255);
}

void game::renderText(std::string text,SDL_Rect dst)
{
    SDL_Color black = {0,0,0};
    SDL_Surface *surf = TTF_RenderText_Solid(font,text.c_str(),black);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer,surf);
    SDL_RenderCopy(renderer,tex,NULL,&dst);
    SDL_FreeSurface(surf);
}

void game::render()
{
    SDL_SetRenderDrawColor(renderer,51, 153, 51,255);
    SDL_RenderClear(renderer);

    PositionLogic(xFace,yFace);
    snake();
    snake_tail();
    food();

    SDL_Rect Score_dst = {width/3,0,100,40};
    renderText("Score:  " + std::to_string(score),Score_dst);

    int minutes = SDL_GetTicks()/(1000*60);
    int seconds = (SDL_GetTicks()/1000) % 60;

    SDL_Rect Time_dst = {width*2/3 - 100,0,200,40};

    renderText("Time:  " + std::to_string(minutes) + " min : " + std::to_string(seconds) + " sec",Time_dst);

    SDL_Rect lives_dst = {50,0,100,40};
    renderText("Lives: " + std::to_string(lives),lives_dst);

    SDL_RenderPresent(renderer);
    SDL_Delay(70);
}

void game::mainLoop()
{
    EventListener();
    update();
    logic();
    render();
}

game::~game()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}
