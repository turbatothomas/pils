#ifndef OGGETTO_H
#define OGGETTO_H

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 

#include "global.h"

class Oggetto {
	/* Ricordarsi che l'origine degli assi è in alto a sinistra */
	protected:
	
	int posx = 0;
	int posy = 0;
	int velx = 0;
	int vely = 0;

	int width;  /* rettangolo */
	int height; /* rettangolo */
	int WIDTH;  /* Screen */
	int HEIGHT; /* Screen */
	bool vivo = true;
	bool stop;

	std::string path;
	SDL_Texture *tex;
	SDL_Rect dst;
	
	public:

	char typeId = ID_ALTRO;

	/* Oggetto( Altezza massima, larghezza massima)*/
	Oggetto();
	Oggetto(int w, int h);
	virtual ~Oggetto();
	void setX(int);
	void setY(int);
	void setW(int);
	void setH(int);
	void setVelX(int);
	void setVelY(int);
	void setWLimit(int a) {WIDTH = a;}
	void setHLimit(int a) {HEIGHT = a;}
	int getX() { return posx; }
	int getY() { return posy; }
	int getW() { return width; }
	int getH() { return height; }

	SDL_Texture *getTexture() { return tex; }
	virtual void processEvents(SDL_Event *e);
	virtual void move();
	void setPath(std::string p);
	virtual void setTexture(SDL_Texture *tex);
	void loadTexture(SDL_Renderer *render);
	void loadTexture(SDL_Renderer *render, std::string path);
	void render(SDL_Renderer *ren);
	std::string getPath();

};

#endif
