#ifndef GIRLS_MANAGER_H
#define GIRLS_MANAGER_H

#include <filesystem>
#include <vector>
#include <list>
#include <iostream>
#include <cmath>
#include <algorithm>

#include "global.h"
namespace fs = std::filesystem;

class GirlsManager {
	const std::string PATH_GIRLS = "girls";
	std::vector<fs::path> girlsDirectories; // directory trovate: girl1, girl2 ecc...
	fs::path imgPath;
	int currentPage; //ogni pagina contiene tre immagini

	public:
	std::string selectedGirl;
	std::list<fs::path> girlImages;

	GirlsManager();
	void getDirs();
	std::vector<std::string> *getPresentationImages();
	fs::path getPresentationImage(fs::path girlPath);
	fs::path getFirstPresentationImageFound(fs::path girlPath);
	void getGirlImages();
	std::string getNextGirlImage();
	void nextImages();

	bool checkPresentationFile(fs::path path);
	void initImages();

};

#endif
