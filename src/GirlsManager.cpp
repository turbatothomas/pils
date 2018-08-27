#include "GirlsManager.h"

GirlsManager::GirlsManager() {
	fs::path absolutePath = getAbsolutePath(PATH_GIRLS);

	imgPath = absolutePath;
	currentPage = 0;
}

/*
 * Ottiene la lista di directory nella cartella girls (girls1, girls2, ecc...)
 */
void GirlsManager::getDirs() {
	if (fs::exists(imgPath) && fs::is_directory(imgPath)) {
		for (auto &subdir: fs::directory_iterator(imgPath)) {
			if (fs::is_directory(subdir)) {
				std::cout << "SubDir: " << subdir.path() << std::endl;
				girlsDirectories.push_back(subdir);
			}
		}
	}
	std::sort(girlsDirectories.begin(), girlsDirectories.end());
}

/*
 * Mi aspetto di trovare l'immagine girl.jpg o png nelle cartelle di ogni ragazza
 */
fs::path GirlsManager::getPresentationImage(fs::path girlPath) {
	if(checkPresentationFile(girlPath / "girl.jpg")) {
		return girlPath / "girl.jpg";
	} else if (checkPresentationFile(girlPath / "girl.png")) {
		return girlPath / "girl.png";
	}

	return fs::path("");
}

/*
 * Recupera il primo file che trova nel caso mancasse girl.jpg o png
 */
fs::path GirlsManager::getFirstPresentationImageFound(fs::path girlPath) {
	for (auto &girlFile: fs::directory_iterator(girlPath)) {
		return girlFile;
	}

	return "";
}

/*
 * recupera tre immagini da mostrare nel menu all'inizio del gioco
 */
std::vector<std::string> *GirlsManager::getPresentationImages() {
	std::vector<std::string> *treImmagini = new std::vector<std::string>();
	treImmagini->push_back("");
	treImmagini->push_back("");
	treImmagini->push_back("");

	/* indice da cui partire */
	int j = currentPage * 3;
	/* tiene conto delle immagini ottenute (max 3 alla volta)*/
	int i = 0;
	/* usata per saltare le immagini se ce né bisogno */
	int c = 0;

	for (auto &dir: girlsDirectories) {
		if (c < j) {
			c++;	/*Questa parte di codice fa leggermente schifo ma funziona :)*/
			continue;
		}

		if(dir.string().find(fs::path("girls/girl").make_preferred().string()) == std::string::npos){
			continue;
		}

		std::cout << "GirlsManager.cpp: OK -> " << dir << std::endl;
		if (dir.empty()) {
			return treImmagini;
		}

		fs::path tmpGirlPath = getPresentationImage(dir);
		if (tmpGirlPath.string() == "") {
			tmpGirlPath = getFirstPresentationImageFound(dir);
		}
		
		treImmagini->at(i) = getAbsolutePath(tmpGirlPath.string());

		if(i == 2)
			break;
		i++;
		c++;
	}

	return treImmagini;
}

/*
 * Pagina successiva nel menú
 */
void GirlsManager::nextImages() {
	float girlsTot = girlsDirectories.size();
	currentPage++;
	std::cout << "GirlsManager.cpp: currentPage++ = " << currentPage 
			  << "\tgirlsTot = " << girlsTot << std::endl;
	if (currentPage >= ceil(girlsTot / 3)) {
		currentPage = 0;
	}
}

/*
 * Recupera le immagini da mostrare durante la partita
 */
void GirlsManager::getGirlImages() {
	std::vector<std::string> tmp;
	for (auto &img : fs::directory_iterator(fs::path(selectedGirl).remove_filename())) {
		if (img.path().string().find("girl.jpg") == std::string::npos) {
			tmp.push_back(img.path().string());
		} else if (img.path().string().find("girl.png") == std::string::npos) {
			tmp.push_back(img.path().string());
		}
	}

	std::sort(tmp.begin(), tmp.end());
	for (auto &i : tmp) {
		girlImages.push_back(fs::path(i));
	}
}

std::string GirlsManager::getNextGirlImage() {
	if (girlImages.empty()) {
		return "";
	}

	fs::path path = girlImages.front();
	girlImages.pop_front();
	return path.string();
}

bool GirlsManager::checkPresentationFile(fs::path path) {
	if (fs::is_regular_file(path)) {
		return true;
	}
	return false;
}

void GirlsManager::initImages() {
	getDirs();
}
