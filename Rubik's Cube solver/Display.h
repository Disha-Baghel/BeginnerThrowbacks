#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>

class Display
{
public:
    Display(const unsigned int& width, const unsigned int& height);
    ~Display();

    const bool& isClosed() const { return m_Closed; }

    void Clear();
    void Update();
private:

    void HandleEvent();

private:
    int m_Width;
    int m_Height;

    bool m_Closed;

    SDL_Window* m_Window;
    SDL_GLContext m_Context;
};

#endif // DISPLAY_H
