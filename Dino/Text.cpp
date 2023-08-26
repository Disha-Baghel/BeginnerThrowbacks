#include "Text.h"

Text::Text()
{
    TTF_Init();
    font = TTF_OpenFont("D:\\vikram\\Dino\\sans.ttf",20);
}

Text::~Text()
{
    TTF_CloseFont(font);
}

void Text::show(SDL_Renderer* renderer,std::string text,SDL_Rect rect)
{
    SDL_Surface* surf = TTF_RenderText_Solid(font,text.c_str(),{117,117,117});
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer,surf);

    int w,h;
    SDL_QueryTexture(tex,0,0,&w,&h);
    rect.w = w;
    rect.h = h;

    SDL_RenderCopy(renderer,tex,NULL,&rect);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
}
