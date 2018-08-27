#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GirlWindow.h"
#include "Player.h"
#include "SubWindow.h"
#include "MBeer.h"
#include "Menu.h"

#define RES_VITA "res/vita.png"

class Game {
	SDL_Window  *win;
	SDL_Renderer *render;
	SDL_Surface *screenSurface;

	int WIDTH;
	int HEIGHT;
	int FPS = 60;
	int PER_FRAME = 16;	// 1000 / FPS
	int vite;		// 3 vite
	int selected_girl;
	//Oggetto *life[3];
	std::vector<Oggetto*> life;
	Oggetto *girlImage;

	SubWindow *gioco;
	GirlWindow *girlWindow;
	Menu *menu;
	GirlsManager *girlsManager;

	public:
	Game();
	virtual ~Game();
	bool init(const char* titolo, int xpos, int ypos, int flags);
	bool init(const char* titolo);
	SDL_Texture* loadTex(std::string path);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
	
	bool checkCollision(Oggetto *birra, Oggetto *cassa);
	void menuLoop();
	void gameLoop();
};

#endif
