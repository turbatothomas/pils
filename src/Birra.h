#ifndef BOTTLE_H
#define BOTTLE_H

#include <string>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>

#include "Oggetto.h"
#include "PhysicObject.h"


class Birra: public PhysicObject {
	public:
	Birra(int w, int h);
	virtual ~Birra();
	void render(SDL_Renderer *ren);
	void processEvents(SDL_Event *e);

	private:
	int random_x;
};

#endif
