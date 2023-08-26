#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL_image.h>
#include <string>
#include <map>

class Image{
    static SDL_Renderer* renderer;
    std::map<std::string,SDL_Texture*> TextureMap;
    static Image* Instance;
    Image(){}
public:
    static Image* GetInstance(){return Instance = (Instance!=nullptr)?Instance: new Image();}
    static void SetRenderer(SDL_Renderer* rend){renderer = rend;}
    void Load(std::string ImageId,std::string FileName);
    void Show(std::string ImageId,SDL_Rect rect,float rotateAngle=0);
};

#endif // IMAGE_H
