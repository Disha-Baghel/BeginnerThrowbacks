#include "ImageLoad.h"

// Worsy implementation I've ever seen. Stupid.

void show_image(SDL_Renderer* renderer,const char* image,SDL_Rect dst_rect)
{
    SDL_Surface* surf = IMG_Load(image);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer,surf);
    SDL_RenderCopy(renderer,tex,NULL,&dst_rect);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
}
