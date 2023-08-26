#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class game
{
    SDL_Window *window;

    Uint32 prevtime;

    SDL_Rect snake_face;
    SDL_Rect foodRect;
    SDL_Rect tailRect;

    TTF_Font *font;

    int xFace,yFace;
    int score;
    int xFood,yFood;
    int tailX[120],tailY[120];
    int ntail;
    int lives;

    enum direction {stop,left,right,up,down} dir,prev_dir;

    void EventListener();
    void update();
    void render();
    void logic();
    void snake();
    void food();
    void snake_tail();
    void renderText(std::string text,SDL_Rect dst);
    float xPos(int,int,int,int,int);
    float yPos(int,int,int,int,int);
    void PositionLogic(int x,int y);

public:

    bool gameover;
    bool run;
    SDL_Renderer *renderer;
    game();
    ~game();
    void mainLoop();
};
