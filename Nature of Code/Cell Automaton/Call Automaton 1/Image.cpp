#include "Image.h"

SDL_Renderer* Image::renderer;

Image::Image(const char* file,RectMode rm)
{
    loadImage(file);
    setRectMode(rm);
}

void Image::loadImage(const char* file)
{
    SDL_Surface* surface = IMG_Load(file);
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
}

void Image::setRectMode(RectMode rm)
{
    rectMode = rm;
}

void Image::show(const SDL_Rect* dst,const SDL_Rect* src)
{
    switch(rectMode)
    {
        case NONE: SDL_RenderCopy(renderer,texture,src,dst); break;
        case CENTER: SDL_Rect dest = {dst->x-dst->w,dst->y-dst->h,2*dst->w,2*dst->h};
                     SDL_RenderCopy(renderer,texture,src,&dest);break;
    }
}

Image::~Image()
{
    SDL_DestroyTexture(texture);
}
