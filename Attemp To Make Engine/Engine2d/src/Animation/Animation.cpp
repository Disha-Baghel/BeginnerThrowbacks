#include "Animation.h"
#include "TextureManager.h"
#include <iostream>

void Animation::update(){
    SpriteFrame = (SDL_GetTicks()/AnimDelay) % FrameCount;
}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight){
    TextureManager::GetInstance()->DrawFrame(TextureID,x,y,spriteWidth,spriteHeight,SpriteRow,SpriteFrame,Flip);
}

void Animation::setProps(std::string textureID, int spriteRow, int frameCount, int animDelay, SDL_RendererFlip flip){
    TextureID = textureID;
    SpriteRow = spriteRow;
    FrameCount = frameCount;
    AnimDelay = animDelay;
    Flip = flip;
}
