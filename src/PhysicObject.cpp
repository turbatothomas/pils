#include "PhysicObject.h"


PhysicObject::PhysicObject()
{
	PhysicObject(0, 0);
}

PhysicObject::PhysicObject(int w, int h): Oggetto(w, h)
{
}

PhysicObject::~PhysicObject()
{
}

void PhysicObject::caduta()
{
	/* V=ds/dt ds=V*dt */
	unsigned int now = SDL_GetTicks();
	unsigned int dt = now - first_t;
	if ( dt >= 1 && dt < 200) {
		posy += vy * dt / 30;
	}
	first_t = now;
}

/*
 * Ritorna true se i due oggetti
 * si sono scontrati
 */
bool PhysicObject::isCollision(Oggetto *obj1, Oggetto *obj2)
{
	if (obj1->getX() >= obj2->getX() &&
			obj1->getX() <= obj2->getX()+obj2->getW())
	{
		/*
		 * allineati sull'asse delle x
		 */
	}

	return false;	
}

bool PhysicObject::isCollision(int *x, int *y, Oggetto *obj) {
	if (*x >= obj->getX() && *x <= obj->getX() + obj->getW()) {
		if (*y >= obj->getY() && *y <= obj->getY() + obj->getH()) {
			return true;
		}
	}
	return false;
}


bool PhysicObject::isCollidingWith(Oggetto *obj) {
	if (posx+width >= obj->getX() && posx <= obj->getX() + obj->getW()) {
		if (posy + height >= obj->getY()) {
			return true;
		}
	}
	return false;
}

