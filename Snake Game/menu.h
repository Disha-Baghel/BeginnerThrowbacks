#include <SDL2/SDL_image.h>

class menu
{
    SDL_Surface *Menu_still;
    SDL_Surface *Menu_start;
    SDL_Surface *Menu_quit;
    SDL_Surface *Current_surf;
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Texture *Texture;
    int x,y;
public:

    bool run;
    bool gameover;
    menu();
    ~menu();
    void loop();
    void eventListener();
    void image();
    void getRenderer(SDL_Renderer*);
};
