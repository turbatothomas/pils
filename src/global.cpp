#include "global.h"

char *DATA_PATH = NULL;

/*
 * Setta il percorso in cui si trovano immagini e resources
 */
void InitializeDataPath() {
	char *base_path = SDL_GetBasePath();
	if (base_path) {
		DATA_PATH = base_path;
	}
	else {
		DATA_PATH = SDL_strdup("./");
	}
}

/*
 * LIBERA RISORSE!!
 */
void FreeDataPath() {
	SDL_free(DATA_PATH);
}

/*
 * ritorna l'absolute path nel formato nativo dell'os
 */
std::string getAbsolutePath(std::string path) {
	fs::path final_part = path;
	fs::path tmp = fs::path(DATA_PATH) / final_part.make_preferred();
	return tmp.string();
}
