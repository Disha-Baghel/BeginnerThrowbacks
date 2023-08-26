#include "Display.h"
#include "InputManager.h"
#include <GL/glew.h>

Display::Display(const unsigned int& width, const unsigned int& height)
{
    m_Width = width;
    m_Height = height;

    SDL_Init(SDL_INIT_EVERYTHING);

    m_Window = SDL_CreateWindow("Rubik's Cube Solver", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    m_Context = SDL_GL_CreateContext(m_Window);

    glewInit();

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    m_Closed = false;
}

Display::~Display()
{
    SDL_GL_DeleteContext(m_Context);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Display::Clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::Update()
{
    SDL_GL_SwapWindow(m_Window);
    HandleEvent();
}

void Display::HandleEvent()
{
    int ret = Input.Handle();

    if(ret == InputManager::CLOSED)
        m_Closed = true;
    else if(ret == InputManager::RESIZED)
    {
        SDL_GetWindowSize(m_Window, &m_Width, &m_Height);
        glViewport(0,0,m_Width,m_Height);
    }
}
