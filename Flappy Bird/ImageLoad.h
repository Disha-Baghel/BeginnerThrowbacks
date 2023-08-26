#ifndef IMAGELOAD_H
#define IMAGELOAD_H

#include <SDL2/SDL_image.h>

inline SDL_Texture* loadImage(SDL_Renderer *ren,const char* file)
{
    SDL_Surface *surf= IMG_Load(file);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren,surf);
    SDL_FreeSurface(surf);
    return tex;
}
#endif // IMAGELOAD_H
