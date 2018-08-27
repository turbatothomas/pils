#include "GirlWindow.h"

GirlWindow::GirlWindow(int w, int h, SDL_Renderer *r, GirlsManager *gManager) : SubWindow(w, h, r) {

	ren = r;
	girlsManager = gManager;

	girlImage = new Oggetto(width, height);

	girlsManager->getGirlImages();
	currentimg = girlsManager->getNextGirlImage();

	girlImage->setX(0);
	girlImage->setY(0);

	girlImage->loadTexture(ren, currentimg);

	addObject(girlImage);
}

bool GirlWindow::showNextGirl() {
	currentimg = girlsManager->getNextGirlImage();
	if (currentimg == "") {
		return false;
	}
	girlImage->loadTexture(ren, currentimg);

	return true;
}
