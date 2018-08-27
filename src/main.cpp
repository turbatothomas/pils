#include "Game.h"

using namespace std;

int main(int argc, char* argv[])
{
	Game *g = new Game();
	if (g->init("PILSNER++")) {
		g->menuLoop();
		g->gameLoop();
	}

	delete g;
	return 0;
}


