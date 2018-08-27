#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <SDL2/SDL.h>

#include "Oggetto.h"
#include "global.h"

class Player : public Oggetto {
	public:
	/* Player( Altezza massima, larghezza massima)*/
	Player(int w, int h);
	~Player();
	void move();
	void render(SDL_Renderer *ren);
	void processEvents(SDL_Event *e);

	private:
	int mousex;
	int mousey;
};

#endif
