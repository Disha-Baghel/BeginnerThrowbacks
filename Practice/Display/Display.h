#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>

class Display
{
public:
    Display(unsigned int width, unsigned int height, const char* const &Title);

    void Update();
    bool IsClosed();
    void Clear(float r,float g, float b, float a);

    virtual ~Display();
protected:

private:
    Display(const Display& other) = delete;
    Display& operator=(const Display& rhs) = delete;

    SDL_Window* m_Window;
    SDL_GLContext m_glContext;

    bool m_isClosed;
};

#endif // DISPLAY_H
