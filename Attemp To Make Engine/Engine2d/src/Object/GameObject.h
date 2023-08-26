#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IObject.h"
#include "Transform.h"
#include <SDL2/SDL.h>

struct Properties {
    float X,Y;
    int Width,Height;
    SDL_RendererFlip Flip;
    std::string TextureID;

    Properties(std::string textureID,float x,float y,int width,int height,SDL_RendererFlip flip = SDL_FLIP_NONE) {
        X = x;
        Y = y;
        Flip = flip;
        Width = width;
        Height = height;
        TextureID = textureID;
    }
};

class GameObject: public IObject {
  public:
    GameObject(Properties* props): TextureID(props->TextureID),
        Width(props->Width),Height(props->Height),Flip(props->Flip) {
        transform = new Transform(props->X,props->Y);
    }

    virtual void Draw() = 0;
    virtual void update(float dt) = 0;
    virtual void Clear() = 0;

  protected:
    Transform* transform;
    std::string TextureID;
    int Width,Height;
    SDL_RendererFlip Flip;
};

#endif // GAMEOBJECT_H
