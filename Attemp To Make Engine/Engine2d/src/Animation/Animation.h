#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <SDL2/SDL.h>

class Animation
{
    public:
        Animation(){}

        void update();
        void Draw(float x,float y,int spriteWidth,int spriteHeight);
        void setProps(std::string textureID,int spriteRow,int frameCount,int animDelay,SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        int SpriteRow,SpriteFrame;
        int AnimDelay,FrameCount;
        std::string TextureID;
        SDL_RendererFlip Flip;
};

#endif // ANIMATION_H
