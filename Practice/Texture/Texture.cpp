#include "Texture.h"
#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>

Texture::Texture(const char* const &ImagePath)
{
    std::fstream file(ImagePath);
    if(!file)
    {
        std::cerr << "Error: " << ImagePath << " not available\n";
        exit(0);
    }
    file.close();

    SDL_Surface* surface = IMG_Load(ImagePath);

    if(surface->pixels == NULL)
    {
        std::cerr << "Error: Failed to load texture (" << ImagePath << ")\n";
        exit(0);
    }

    glGenTextures(1,&m_Texture);
    glBindTexture(GL_TEXTURE_2D, m_Texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLint mode;

    if(surface->format->BytesPerPixel == 3)
        mode = GL_RGB;
    else if(surface->format->BytesPerPixel == 4)
        mode = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0,
                 mode, GL_UNSIGNED_BYTE, surface->pixels);

    SDL_FreeSurface(surface);
}

Texture::~Texture()
{

}

void Texture::Bind(unsigned int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
}
