#ifndef GIRLWINDOW_H
#define GIRLWINDOW_H

#include <list>
#include <iostream>
#include <filesystem>

#include "SubWindow.h"
#include "GirlsManager.h"

namespace fs = std::filesystem;

class GirlWindow: public SubWindow {
	Oggetto *girlImage;

	std::string currentimg;
	std::list<fs::path> girlsImages;

public:
	GirlsManager *girlsManager;
	
	GirlWindow(int w, int h, SDL_Renderer *r, GirlsManager *gManager);
	bool showNextGirl();
};
#endif

