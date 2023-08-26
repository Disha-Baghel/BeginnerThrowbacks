#include "TextureManager.h"

TextureManager* TextureManager::Instance = nullptr;

TextureManager* TextureManager::GetInstance() {
    return Instance = (Instance != nullptr)?Instance:new TextureManager();
}

bool TextureManager::Load(std::string id, std::string filename) {
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface == nullptr) {
        SDL_Log("Failed to load surface from %s: %s",filename.c_str(),SDL_GetError());
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine2d::GetInstance()->GetRenderer(),surface);
    if(texture == nullptr) {
        SDL_Log("Failed ot create texture from surface: %s",SDL_GetError());
        return false;
    }
    TextureMap[id] = texture;
    return true;
}

void TextureManager::Draw(std::string id, int x, int y, int w, int h, SDL_RendererFlip flip) {
    SDL_Rect srcRect = {0,0,w,h};
    SDL_Rect dstRect = {x,y,w,h};
    SDL_RenderCopyEx(Engine2d::GetInstance()->GetRenderer(),TextureMap[id],&srcRect,&dstRect,0,nullptr,flip);
}

void TextureManager::DrawFrame(std::string id,int x,int y,int w,int h,int row,int Frame,SDL_RendererFlip flip) {
    SDL_Rect srcRect = {w*Frame,h*(row-1),w,h};
    SDL_Rect dstRect = {x,y,w,h};
    SDL_RenderCopyEx(Engine2d::GetInstance()->GetRenderer(),TextureMap[id],&srcRect,&dstRect,0,nullptr,flip);
}

void TextureManager::Drop(std::string id) {
    SDL_DestroyTexture(TextureMap[id]);
    TextureMap.erase(id);
}

void TextureManager::Clear() {
    std::map<std::string,SDL_Texture*>::iterator it;
    for(it = TextureMap.begin(); it!=TextureMap.end(); it++)
        SDL_DestroyTexture(it->second);
    TextureMap.clear();
}
