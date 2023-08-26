#include "image.h"

SDL_Texture* Create_Texture(std::string img)
{
    SDL_Renderer* renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));
    SDL_Surface* surface = IMG_Load(img.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    return texture;
}
