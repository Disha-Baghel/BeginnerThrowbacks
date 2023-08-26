#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <map>
#include "Engine2d.h"

class TextureManager {
    std::map<std::string,SDL_Texture*> TextureMap;
    static TextureManager* Instance;
  public:
    static TextureManager* GetInstance();
    bool Load(std::string id, std::string filename);
    void Draw(std::string id,int x,int y,int w,int h,SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawFrame(std::string id,int x,int y,int w,int h,int row,int Frame,SDL_RendererFlip flip = SDL_FLIP_NONE);
    void Clear();
    void Drop(std::string id);
};

#endif // TEXTUREMANAGER_H
