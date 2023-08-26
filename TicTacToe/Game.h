#include <SDL2/SDL.h>

class Game
{
public:
	Game();

	bool loop();

	void draw();
	void eventHandler();

	int checkForWin();

	static Game* instance();

	void initTexture();

private:
	SDL_Renderer* m_Renderer;
	SDL_Window* m_Window;	

	SDL_Event m_Event;

	SDL_Texture *m_Circle, *m_Cross;

	bool m_Running;

	static Game* s_GameInstance;

	char m_Matrix[3][3];
	char turn;
};
