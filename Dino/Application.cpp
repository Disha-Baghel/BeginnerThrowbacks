#include "Application.h"
#include <sstream>
#include <fstream>

Application* Application::Application_instance = new Application();

Application* Application::Instance()
{
    if(Application::Application_instance == NULL)
        Application::Application_instance = new Application();

    return Application_instance;
}

Application::Application()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(800,500,0,&window,&renderer);
    this->running = true;
    dino = new Dino();
    text = new Text();
    score = 0;

    std::fstream file("save.save");
    file>>high_score;
    file.close();
}

Application::~Application()
{
    if(score > high_score)
    {
        std::ofstream file("save.save");
        file<<score;
        file.close();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Application::loop()
{
    EventHandler();
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    dino->show();
    std::stringstream ss;
    if(Dino::Game_started)
    {
        score+=0.15;
        if((int)score%700 == 0)
            cactus::velocity += 0.05;
        ss<<"HI   "<<((int)high_score>(int)score?(int)high_score:(int)score)<<"   "<<(int)score;
    }
    //text->show(renderer,ss.str(),{600,50,200,50});
    SDL_RenderPresent(renderer);
    return running;
}

void Application::EventHandler()
{
    if(SDL_PollEvent(&Dino::event))
    {
        switch(Dino::event.type)
        {
            case SDL_QUIT: running = false;
                            delete Application_instance;
                            break;
        }
    }
}
