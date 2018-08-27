#include "Player.h"

Player::Player(int w, int h): Oggetto(w, h)
{
	velx = 0;
	vely = 0;
	vivo=true;

	mousex = 0;
}

Player::~Player() {}

void Player::move()
{
	posx = mousex-(width/2);
	/*Mantieni la cassa all'interno del campo da gioco*/
    if (posx < 0 ) {
		posx = 0; 
	} else if (posx > WIDTH-(width)) {
		posx = WIDTH - (width);
	}

}

void Player::render(SDL_Renderer *ren)
{
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = posx;
	dst.y = posy;

	if (width == 0 || height == 0) {
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
		width = dst.w;
		height = dst.h;
	} else {
		dst.w = width;
		dst.h = height;
	}

	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void Player::processEvents(SDL_Event *e)
{
	switch (e->type) {
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&mousex, NULL);
			break;
	}
}
