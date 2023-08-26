#include <SDL2/SDL_image.h>

enum RectMode{NONE,CENTER};

class Image
{
    SDL_Texture* texture;
    RectMode rectMode;
public:
    static SDL_Renderer* renderer;
    Image(const char* file,RectMode rm = NONE);
    ~Image();
    void setRectMode(RectMode rm);
    void loadImage(const char* file);
    void show(const SDL_Rect* dst,const SDL_Rect* src = NULL);
};
