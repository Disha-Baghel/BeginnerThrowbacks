#include "Image.h"

Image* Image::Instance = nullptr;
SDL_Renderer* Image::renderer;

void Image::Load(std::string ImageId,std::string FileName){

    try{
        if(renderer == nullptr)
            throw "renderer not defined in Image::Load \n";

        SDL_Surface* Surface = IMG_Load(FileName.c_str());

        if(Surface == nullptr)
            throw "Couldn't Create Surface from Source: " + FileName;

        SDL_Texture* Texture = SDL_CreateTextureFromSurface(renderer,Surface);

        if(Texture == nullptr)
            throw "Couldn't Create Texture from Surface: " + FileName;

        TextureMap[ImageId] = Texture;
        SDL_FreeSurface(Surface);

    }catch(std::string Error){
        SDL_Log(Error.c_str());
        exit(0);
    }
}

void Image::Show(std::string ImageId,SDL_Rect rect,float rotateAngle){
    SDL_RenderCopyEx(renderer,TextureMap[ImageId],NULL,&rect,rotateAngle,nullptr,SDL_FLIP_NONE);
}
