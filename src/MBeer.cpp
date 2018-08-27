#include "MBeer.h"

MBeer::MBeer(SDL_Renderer *r, int *lifes) {
	renderer = r;
	this->lifes = lifes;
	livello = 0;
	rng = std::mt19937(rd());
}

MBeer::~MBeer() {
	SDL_DestroyTexture(beerTexture);
}

int MBeer::casual(int sn, int en)
{
	return (rand() % en-sn) + sn;
}

int MBeer::randomVelY()
{
	//TODO Da sistemare
	uni = std::uniform_int_distribution(1, livello * 2 + 2);
	return uni(rng);
}

Birra* MBeer::lasciaBirra()
{
	/*DIO CANEE dopo aver aggiunto questo cout non ci sono piú errori di segmentazione*/
	Birra *tmp = new Birra(0, 0);
	tmp->vy += randomVelY();
	
	std::cout<<"lasciaBirra() vely = "<< tmp->vy <<std::endl;
	tmp->setWLimit(width); // limite di fine campo di gioco

	tmp->setTexture(beerTexture);
	int x = casual(0, width-20);
	tmp->setX(x);
	//faccio apparire le birre da fuori dalla finestra
	tmp->setY(startBeerY);
	birre.push_back(tmp);

	return tmp;
}

void MBeer::run()
{
	if (gameOver) {
		return;
	}

	uni = std::uniform_int_distribution(0, probCadutaBirre);
	if (uni(rng) < 1 && birre.size() < maxBeers) {
		lasciaBirra();
	}
	if (birre.size() < 1)
		lasciaBirra();

	std::list<Birra*>::iterator birra = birre.begin();
	while ( birra != birre.end()) {
		if (birre.size() <= 0) break;
		(*birra)->caduta();
		if ((*birra)->isCollidingWith(cassa)) {
			punteggio += 1;
			std::cout << "Punteggio: " << punteggio << std::endl;
			/*Aumenta il livello di difficolta ogni 20 punti*/
			if ((punteggio % SOGLIA_CAMBIO_IMMAGINE) == 0) {
				livello++;
				// Aumenta il massimo numero di birre per ogni livello
				maxBeers += livello * 2;
				probCadutaBirre -= 2;
			}
			std::cout << "Livello: " << livello << std::endl;
			birra = birre.erase(birra);
		}
		else if ((*birra)->getY() + 50 > height) {
			std::cout << "Rimuovo Birra e tolgo vita ~ "<<*lifes << std::endl;
			(*lifes)--;
			birra = birre.erase(birra);
			if (*lifes == 0 ) {
				maxBeers = 0;
				birre.clear();
				break;
			}
		}
		else {
			++birra;
		}
	}
}

void MBeer::stop() {
	gameOver = true;
	birre.clear();
}

void MBeer::render() {
	for (auto it : birre) {
		it->render(renderer);
	}
}

void MBeer::setTexture(SDL_Texture *tex) {
	beerTexture = tex;
}

void MBeer::setHeight(int h) {
	height = h;
}

void MBeer::setWidth(int w) {
	width = w;
}
