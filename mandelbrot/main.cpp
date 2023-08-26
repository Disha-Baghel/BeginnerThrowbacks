#include <SDL2/SDL.h>
#include <complex>

enum {Width = 800, Height = 500};

void drawMandlebrot(SDL_Renderer* renderer, const double zoom);

int main(int argc, char** argv)
{

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("MandleBrot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_bool running = SDL_TRUE;

    double zoom = 4.0;

    SDL_Event event;

    SDL_bool drawAgain = SDL_TRUE;

    while(running) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT: running = SDL_FALSE;
                                break;
                case SDL_KEYDOWN: drawAgain = SDL_TRUE;
                    switch(event.key.keysym.sym) {
                        case SDLK_KP_PLUS: zoom -= 0.5; break;
                        case SDLK_KP_MINUS: zoom += 0.5; break;
                    }
            }
        }

        if(drawAgain) {

            SDL_SetRenderDrawColor(renderer, 0,0,0,255);
            SDL_RenderClear(renderer);

            drawMandlebrot(renderer, zoom);

            SDL_RenderPresent(renderer);

            drawAgain = SDL_FALSE;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void drawMandlebrot(SDL_Renderer* renderer, const double zoom) {
    constexpr double diffHalf = (Width - Height)/2;

    for(int y=0; y < Height; ++y) {
        for(int x = 0; x < Width; ++x) {
            std::complex<double> c(1.0 * (x-diffHalf)/Height * zoom - 2.0, 1.0 * y/Height * zoom - 2.0);
            std::complex<double> z(0,0);
            int count = 0;
            while(count < 255) {
                z = z*z + c;
                if(abs(z) > 2.0)
                    break;
                count++;
            }
            SDL_SetRenderDrawColor(renderer, Width * count, Width * count, Width * count, 0xff);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}
