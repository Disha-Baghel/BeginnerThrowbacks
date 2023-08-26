#include <iostream>
#include <gl/glew.h>
#include "Display.h"
#include "../InputManager/InputManager.h"

Display::Display(unsigned int width, unsigned int height, const char* const &Title)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4);

    m_Window = SDL_CreateWindow(Title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    m_glContext = SDL_GL_CreateContext(m_Window);

    glewExperimental = GL_TRUE;
    GLenum status = glewInit();

    m_isClosed = false;

    if(status != GLEW_OK)
    {
        std::cout << "Glew failed to initialize!" << std::endl;
        m_isClosed = true;
        return;
    }

    SDL_GL_SetSwapInterval(1);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);

    glEnable(GL_SRGB);

    glViewport(0,0,width,height);
}

Display::~Display()
{
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

bool Display::IsClosed()
{
    return m_isClosed;
}

void Display::Clear(float r,float g,float b,float a)
{
    glClearColor(r,g,b,a);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::Update()
{
    SDL_GL_SwapWindow(m_Window);

    int eventType = InputInstance->Handle();

    if(eventType == InputManager::CLOSED)
        m_isClosed = true;
    else if(eventType == InputManager::RESIZED)
    {
        int w,h;
        SDL_GetWindowSize(m_Window,&w,&h);
        glViewport(0,0,w,h);
    }
}
