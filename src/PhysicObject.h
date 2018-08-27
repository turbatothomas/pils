#ifndef FISICA_H
#define FISICA_H

/*
 * in pratica qua sdl solo per SDL_GetTicks()
 */
#include "SDL2/SDL.h"
#include "Oggetto.h"

class PhysicObject : public Oggetto {
	int limit_x;
	int limit_y;
	
	int vmax;

	// usando SDL_GetTicks per prendere il tempo
	unsigned int last_t; //ultimo tempo preso
	unsigned int first_t = 0;//il primp

	public:
	double vy = 1;

	PhysicObject();
	PhysicObject(int w, int h);
	~PhysicObject();

	void caduta();

	static bool isCollision(Oggetto *obj1, Oggetto *obj2);
	static bool isCollision(int *x, int *y, Oggetto *obj);

	bool isCollidingWith(Oggetto *obj);
};

#endif
