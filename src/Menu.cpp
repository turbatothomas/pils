#include "Menu.h"

Menu::Menu(int w, int h, SDL_Renderer *r, GirlsManager *gManager): SubWindow(w, h, r) {

	girlsManager = gManager;
	ren = r;

	sfondo = new Oggetto(width, height);
	tile1 = new Oggetto(TILE_WIDTH, TILE_HEIGHT);
	tile2 = new Oggetto(TILE_WIDTH, TILE_HEIGHT);
	tile3 = new Oggetto(TILE_WIDTH, TILE_HEIGHT);
	nextPage = new Oggetto(PAGE_ARROW_SIZE, PAGE_ARROW_SIZE);
	prevPage = new Oggetto(PAGE_ARROW_SIZE, PAGE_ARROW_SIZE);

	imgsfondo = getAbsolutePath("res/sfondo.jpg");
	
	girlsManager->initImages();
	setPresentationImages();

	sfondo->loadTexture(ren, imgsfondo);
	nextPage->loadTexture(ren, getAbsolutePath("res/arrow-right.png"));
	prevPage->loadTexture(ren, getAbsolutePath("res/arrow-left.png"));

	sfondo->setX(0);
	sfondo->setY(0);

	next_page_x = width - 50;
	next_page_y = height - height/2;

	nextPage->setX(next_page_x);
	nextPage->setY(next_page_y);

	prevPage->setX(20);
	prevPage->setY(height + height/2);

	tile1->setX(TILE_BASEX + OFFSET_TILE1);
	tile1->setY(TILE_BASEY);

	tile2->setX(TILE_BASEX + OFFSET_TILE2);
	tile2->setY(TILE_BASEY);

	tile3->setX(TILE_BASEX + OFFSET_TILE3);
	tile3->setY(TILE_BASEY);

	addObject(sfondo);
	addObject(tile1);
	addObject(tile2);
	addObject(tile3);
	addObject(nextPage);
	addObject(prevPage);
}

void Menu::setPresentationImages() {
	std::vector<std::string> *girlsImages = girlsManager->getPresentationImages();

	girl1 = girlsImages->at(0);
	girl2 = girlsImages->at(1);
	girl3 = girlsImages->at(2);
	
	tile1->loadTexture(ren, girl1);
	tile2->loadTexture(ren, girl2);
	tile3->loadTexture(ren, girl3);
}

int Menu::mouseIsOverGirl(int *x, int *y){
	if (x == nullptr || y == nullptr)
		return 0;

	disevidenzia();
	if (PhysicObject::isCollision(x, y, tile1) && girl1 != "") {
		selected_tile = tile1;
		selected_girl = 1;
		girlsManager->selectedGirl= girl1;
	} else if (PhysicObject::isCollision(x, y, tile2) && girl2 != "") {
		selected_tile = tile2;
		selected_girl = 2;
		girlsManager->selectedGirl= girl2;
	} else if (PhysicObject::isCollision(x, y, tile3) && girl3 != "") {
		selected_tile = tile3;
		selected_girl = 3;
		girlsManager->selectedGirl= girl3;
	} else {
		return 0;
	}

	evidenzia(selected_girl);

	return selected_girl;
}

int Menu::mouseClickNextPage(int *x, int *y) {
	if (x == nullptr || y == nullptr)
		return 0;

	if (PhysicObject::isCollision(x, y, nextPage)) {
		std::cout << "Clicked NextPage" << std::endl;
		girlsManager->nextImages();
		setPresentationImages();
		return 1;
	}

	return 0;
}

int Menu::mouseClickPrevPage(int *x, int *y) {
	if (x == nullptr || y == nullptr)
		return 0;

	if (PhysicObject::isCollision(x, y, prevPage)) {
		std::cout << "Clicked PrevPage" << std::endl;
		return 1;
	}

	return 0;
}

void Menu::evidenzia(int ntile) {
	if (!evidenziato) {
		int curx = selected_tile->getX();
		int cury = selected_tile->getY();

		selected_tile->setX(curx + ANIMATION_X_UP);
		selected_tile->setY(cury + ANIMATION_Y_UP);
		evidenziato = !evidenziato;
	} 
}

void Menu::disevidenzia() {
	tile1->setX(TILE_BASEX + OFFSET_TILE1);
	tile1->setY(TILE_BASEY);

	tile2->setX(TILE_BASEX + OFFSET_TILE2);
	tile2->setY(TILE_BASEY);

	tile3->setX(TILE_BASEX + OFFSET_TILE3);
	tile3->setY(TILE_BASEY);

	evidenziato = false;
}
