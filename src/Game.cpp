#include "Game.h"

#define DELAY 30	//1000 = 1s

#define WIDTH 800
#define HEIGHT 500
#define GIRLIMG_SUBWINDOW_WIDTH 200
#define GAME_SUBWINDOW_WIDTH (WIDTH - GIRLIMG_SUBWINDOW_WIDTH)
#define GAME_SUBWINDOW_HEIGTH HEIGHT

using namespace std;

Game::Game()
{
	FPS = 60;
	PER_FRAME = 1000 / FPS;
	vite = 3;
}

Game::~Game()
{
	//SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(win);
	win = nullptr;
	render = nullptr;
	IMG_Quit();
	SDL_Quit();
}

bool Game::init(const char* titolo, int xpos, int ypos, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Errore nell'inizializzare SDL: " << SDL_GetError() << endl;
		return false;
	}
	win = SDL_CreateWindow(titolo, xpos, ypos, WIDTH, HEIGHT, flags);
	if (win == nullptr) {
		cout << "Errore nella creazione della finestra: " << SDL_GetError() << endl;
		SDL_Quit();
		return false;
	}

	render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (render == nullptr) {
		cout << "Errore nella creazione del render: " << SDL_GetError() << endl;
		SDL_Quit();
		return false;
	}

	InitializeDataPath();

	gioco = new SubWindow(WIDTH - GIRLIMG_SUBWINDOW_WIDTH, HEIGHT, render);
	girlsManager = new GirlsManager();
	return true;
}

bool Game::init(const char* titolo)
{
	return init(titolo, 100, 100, SDL_WINDOW_SHOWN);
}

SDL_Texture* Game::loadTex(string path)
{
	SDL_Texture *tex = nullptr;

	SDL_Surface *sur = IMG_Load(path.c_str());
	if (sur == nullptr) {
		exit(1);
	}

	tex = SDL_CreateTextureFromSurface(render, sur);
	SDL_FreeSurface(sur);

	if (tex == nullptr) {
		exit(1);
	}

	return tex;
}


void Game::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void Game::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

bool Game::checkCollision(Oggetto *birra, Oggetto *cassa)
{
	int fondob = birra->getY() + birra->getH();
	int cimac = birra->getY();
	int bx, bw, cx, cw;
	bx = birra->getX();
	bw = birra->getW();
	cx = cassa->getX();
	cw = cassa->getW();

	if (fondob >= cimac) {
		if ((bx >= cx && bx <= cx+cw) ||
				(bx+bw >= cx && bx+bw <= cx+cw)) {
			return true;
		}
	}

	return false;
}

void Game::gameLoop()
{
	SDL_Event e;
	bool quit = false;
	int prevVite = vite;
	int livello = 0;

	MBeer *mbeer = new MBeer(render, &vite);
	Oggetto *sfondo = new Oggetto(WIDTH, HEIGHT);
	Oggetto *gameOver = new Oggetto(370, 260);
	Player *player = new Player(100, 80);

	/*Creo spazio per le girlssss*/
	girlWindow = new GirlWindow(GIRLIMG_SUBWINDOW_WIDTH, HEIGHT, render, girlsManager);
	girlWindow->setX(WIDTH-GIRLIMG_SUBWINDOW_WIDTH);
	girlWindow->setY(0);

	gioco->setX(0);
	gioco->setX(0);

	gioco->addObject(sfondo);

	mbeer->width = WIDTH - GIRLIMG_SUBWINDOW_WIDTH;
	mbeer->setTexture(loadTex(getAbsolutePath("res/bottiglia.jpg").c_str()));
	mbeer->setHeight(HEIGHT);
	mbeer->setWidth(GAME_SUBWINDOW_WIDTH);
	mbeer->setCassa(player);

	srand(time(NULL));

	int cur_x_vita = 5;
	const int distanzaTraLeVite = 30;
	for (int i = 0; i < 3; i++) {
		life.push_back(new Oggetto(20, 20));
		life[i]->typeId = ID_VITA;
		life[i]->loadTexture(render, getAbsolutePath(RES_VITA));
		life[i]->setX(cur_x_vita);
		life[i]->setY(HEIGHT - 30);
		cur_x_vita += distanzaTraLeVite;
		gioco->addObject(life[i]);
	}

	player->setWLimit(WIDTH);

	sfondo->loadTexture(render, getAbsolutePath("res/sfondo.jpg"));
	gameOver->loadTexture(render, getAbsolutePath("res/gameover.png"));
	player->loadTexture(render, getAbsolutePath("res/cassa.jpg"));

	player->setX(WIDTH/2);
	player->setY(HEIGHT - player->getH());

	gameOver->setX(50);
	gameOver->setY(20);

	gioco->addObject(player);

	std::cout << "Pronti per partire con il loop del gioco" << std::endl;

	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;
			else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_a) {
					std::cout << "Porco DIOOOOOO!" << std::endl;
				}
			}
			player->processEvents(&e);
		}

		player->move();
		mbeer->run();

		if(vite < prevVite) {
			gioco->removeObject(life[vite]);
			prevVite = vite;
			if(vite == 0) {
				//GameOver'
				mbeer->stop();
				gioco->addObject(gameOver);
			}
		}
		if(mbeer->livello != livello) {
			girlWindow->showNextGirl();
			livello = mbeer->livello;
		}
		
		SDL_RenderClear(render);

		girlWindow->render();
		gioco->render();
		mbeer->render();

		SDL_RenderPresent(render);
		SDL_Delay(DELAY);
	}

	delete gioco;
	delete girlWindow;
}

void Game::menuLoop() {
	SDL_Event event;
	bool quit = false;

	menu = new Menu(WIDTH, HEIGHT, render, girlsManager);

	int mousex, mousey;

	while(!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					std::exit(0);
					break;
				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&mousex, &mousey);
					selected_girl = menu->mouseIsOverGirl(&mousex, &mousey);
					break;
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&mousex, &mousey);
					selected_girl = menu->mouseIsOverGirl(&mousex, &mousey);
					menu->mouseClickNextPage(&mousex, &mousey);
					menu->mouseClickPrevPage(&mousex, &mousey);
					if (selected_girl > 0) return;
					break;
			}
		}
		menu->render();
		SDL_RenderPresent(render);
		SDL_Delay(DELAY);
	}

	delete menu;
}
