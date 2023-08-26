#include <SDL2/SDL_ttf.h>
#include <string>

class Text
{
    TTF_Font* font;
public:
    Text();
    ~Text();
    void show(SDL_Renderer* renderer,std::string text,SDL_Rect rect);
};
