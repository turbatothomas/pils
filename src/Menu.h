#ifndef MENU_H
#define MENU_H

#include "GirlsManager.h"
#include "SubWindow.h"
#include "PhysicObject.h"
#include <string>

const int PAGE_ARROW_SIZE = 60;

class Menu : public SubWindow {
	static const int TILE_WIDTH = 180;
	static const int TILE_HEIGHT = 300;
	static const int TILE_BASEX = 120;
	static const int TILE_BASEY = 100;

	static const int OFFSET_TILE1 = 0;
	static const int OFFSET_TILE2 = 200;
	static const int OFFSET_TILE3 = 400;

	static const int ANIMATION_X_UP = 10;
	static const int ANIMATION_Y_UP = 10;

	int next_page_x;
	int next_page_y;
	int prev_page_x;
	int prev_page_y;

	std::string imgsfondo;
	std::string girl1;
	std::string girl2;
	std::string girl3;
	
	Oggetto *sfondo;
	Oggetto *tile1, *tile2, *tile3;
	Oggetto *nextPage, *prevPage;
	Oggetto *selected_tile;

	bool evidenziato = false;
	int selected_girl;

public:
	GirlsManager *girlsManager;
	
	Menu(int w, int h, SDL_Renderer *r, GirlsManager *gManager);
	int mouseIsOverGirl(int *x, int *y);
	int mouseClickNextPage(int *x, int *y);
	int mouseClickPrevPage(int *x, int *y);
	void evidenzia(int ntile);
	void disevidenzia();
	void setPresentationImages();
};
#endif

