#include "Oggetto.h"

Oggetto::Oggetto()
{
	posx = 0;
	posy = 0;
	Oggetto(100, 100);
}

Oggetto::Oggetto(int w, int h)
{
	width = w;
	height = h;
	tex = nullptr;
}

Oggetto::~Oggetto()
{
	SDL_DestroyTexture(tex);
	std::cout << "Autodistruzione Oggetto" << std::endl;
	tex = nullptr;
}

void Oggetto::setX(int n)
{
	posx = n;
}

void Oggetto::setY(int n)
{
	posy = n;
}

void Oggetto::setW(int n)
{
	width = n;
}

void Oggetto::setH(int n)
{
	height = n;
}

void Oggetto::setVelX(int n)
{
	velx = n;
}

void Oggetto::setVelY(int n)
{
	vely = n;
}

void Oggetto::setPath(std::string p)
{
	path = p;
}

void Oggetto::loadTexture(SDL_Renderer *render)
{
	loadTexture(render, path);

}

void Oggetto::loadTexture(SDL_Renderer *render, std::string path)
{
	if (tex != nullptr) {
		SDL_DestroyTexture(tex);
	}	
	tex = nullptr;
	
	Uint32 rmask = 0xff000000;
	Uint32 gmask = 0x00ff0000;
	Uint32 bmask = 0x0000ff00;
	Uint32 amask = 0x000000ff;

	SDL_Surface *sur = IMG_Load(path.c_str());
	if (sur == nullptr) {
		std::cout << "Oggetto.cpp: errore nel caricare la surface " << path << " " << IMG_GetError() << std::endl;
		sur = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
	}

	tex = SDL_CreateTextureFromSurface(render, sur);
	SDL_FreeSurface(sur);

	if (tex == nullptr) {
		std::cout << "Oggetto.cpp: errore nel creare la Texture\n";
	}

	std::cout << FILELINE(__LINE__) << " " << path << std::endl;
}

void Oggetto::processEvents(SDL_Event *e)
{
}

void Oggetto::move()
{
}


void Oggetto::render(SDL_Renderer *ren)
{
	//Setup the destination rectangle to be at the position we want

	if (tex == nullptr) {
		std::cout << "Oggetto.cpp: impossibile renderizzare la texture" << std::endl;
		return;
	}
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

std::string Oggetto::getPath()
{
	return path;
}

void Oggetto::setTexture(SDL_Texture *tex) {
	this->tex = tex;
}
