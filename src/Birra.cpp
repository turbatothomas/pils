#include "Birra.h"

Birra::Birra(int w, int h): PhysicObject(w, h)
{
	vely = 1;
}

Birra::~Birra() {
}

void Birra::render(SDL_Renderer *ren)
{
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

void Birra::processEvents(SDL_Event *e)
{
}
