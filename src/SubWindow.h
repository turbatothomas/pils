#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <SDL2/SDL.h>
#include <vector>
#include <list>
#include "Oggetto.h"

class SubWindow {
	protected:
	int width = 10;
	int height = 10;
	int x = 0;
	int y = 0;

	SDL_Rect viewport;
	SDL_Renderer *ren;

	private:

	std::list<Oggetto *> objs;

	public:
	SubWindow(int w, int h, SDL_Renderer *r);
	virtual ~SubWindow();
	bool addObject(Oggetto *obj);
	void removeObject(Oggetto *obj);
	void render();
	int getW() { return width; }
	int getH() { return height; }
	void setX(int _x) {
		x = _x;
		viewport.x = x;
	}
	void setY(int _y) {
		y = _y;
		viewport.y = y;
	}

};

#endif
