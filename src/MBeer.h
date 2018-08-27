/*
 * Gestore delle birre
 * decide il momento e dove far cadere le birre
 */
#ifndef MBEER_H
#define MBEER_H

#include "Birra.h"
#include <list>
#include <random>

#include <SDL2/SDL.h>

#define SOGLIA_CAMBIO_IMMAGINE 10

class MBeer {
	const int startBeerY = -30;

	bool gameOver = false;
	int *lifes;
	int height = 0;
	int probCadutaBirre = 30; // diminuire per aumentare probabilitá
	unsigned int maxBeers = 3;
	SDL_Renderer *renderer;
	SDL_Texture *beerTexture;
	Oggetto *cassa;
	std::list<Birra*> birre;

	// Randoms
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> uni;

	public:
	int width = 600;
	int punteggio = 0;
	int livello = 0;

	MBeer(SDL_Renderer *r, int *lifes);
	~MBeer();
	int casual(int sn, int en);
	int randomVelY();
	Birra* lasciaBirra();
	void run();
	void stop();
	void render();
	void setTexture(SDL_Texture *tex);
	void setHeight(int h);
	void setWidth(int w);
	void setMaxBeers(int m) {maxBeers = m;}
	void incMaxBeers() {maxBeers += 1;}
	void setCassa(Oggetto *obj) {cassa = obj;}
};

#endif
