#include "checkML.h"

#include "Game.h"


// Formato de la especificación de una textura
struct TextureSpec
{
	const char* name;	// Ruta del archivo
	uint numColumns;	// Num de frames por fila
	uint numRows;		// Num de frames por columna
};

// Directorio raiz de los archivos de textura
const string textureRoot = "../assets/images/";

// Especificacion de las texturas del juego
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec
{
	TextureSpec	{"background.png", 9, 7},
				{"mario.png", 12, 1},
				{"supermario.png", 22, 1},
				{"blocks.png", 6, 1},
				{"goomba.png", 3, 1},
				{"koopa.png", 4, 1},
				{"mushroom.png", 1, 1},
				{"coin.png", 4, 1},
				{"lift.png", 1, 1},
				{"numbers.png", 10, 1},
};

Game::Game()
	: seguir(true), 
	mapOffset(0), 
	//mapOffset(5880), // para probar cambio de nivel
	//mapOffset(4080), // para probar el lift en level 2
	points(0),
	nextObject(0),
	marioState(0),
	level(1),
	lastLevel(2), // numero de niveles que tiene el juego
	gameWon(false)
{
	/// ===== Ventana de SDL =====
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Super Mario",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH,
		WIN_HEIGHT,
		SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == nullptr || renderer == nullptr)
		throw "Error cargando SDL"s;


	/// ===== Inicializacion del juego =====

	// Carga las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i)
		textures[i] = new Texture(renderer,
			(textureRoot + textureSpec[i].name).c_str(),
			textureSpec[i].numRows,
			textureSpec[i].numColumns);

	// Carga el tilemap y los objetos segun el nivel
	loadLevel(level);


}

Game::~Game()
{
	// Elimina los objetos del juego
	for (auto obj : sceneObjects) {
		delete obj;
	}

	// Elimina los objetos de la cola de objetos
	for (auto obj : objectQueue) {
		delete obj;
	}
	objectQueue.clear();

	// Elimina las texturas
	for (Texture* texture : textures)
		delete texture;

	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::loadLevel(int l)
{
	cout << "Load level " << l << endl;

	string root = "../assets/maps/world" + to_string(l) + ".csv";

	tilemap = new TileMap(this, root);
	objectQueue.push_back(tilemap);

	loadObjectMap("../assets/maps/world" + to_string(l) + ".txt");
}

void Game::loadObjectMap(const string& mapFile)
{
	ifstream file(mapFile);

	if (!file.is_open()) {
		throw string("fichero de mapa worldX.txt no encontrado");
	}

	string line;

	getline(file, line); // lectura primera linea

	// Usamos un stringstream para leer la linea como si fuera un flujo
	stringstream lineStream(line);

	lineStream >> r >> g >> b;

	while (getline(file, line)) 
	{
		stringstream lineStream(line);

		char tipo, atrib, accion;
		double x, y, sp;

		lineStream >> tipo >> x >> y;

		if(tipo == 'B') lineStream >> atrib >> accion;
		if(tipo == 'L') lineStream >> sp;

		// conversion
		x = x * TILE_SIDE;
		y = y * TILE_SIDE;

		switch (tipo) {
		case 'M':
			if (player == nullptr) {
				player = new Player(this, x, y);
				//player = new Player(this, 4366, 300); // para probar el lift
				//player = new Player(this, 6166, 448); // para probar bandera

				objectQueue.push_back(player);
			}
			else 
			{ // si el player no es null entonces reposicionamos donde diga
				//player.onlevelreload?¿?
				// usar x e y nuevas
				cout << "No se crea nuevo Mario. " << endl;
			}
			
			break;
		case 'B':
			objectQueue.push_back(new Block(this, x, y, atrib, accion));
			break;
		case 'G':
			objectQueue.push_back(new Goomba(this, x, y));
			break;
		case 'K':
			objectQueue.push_back(new Koopa(this, x, y));
			break;
		case 'L':
			objectQueue.push_back(new Lift(this, x, y, sp));
			break;
		case 'C':
			objectQueue.push_back(new Coin(this, x, y));
			break;
		}		
	}

	file.close();

	if (gameWon)
	{
		mapOffset = 0;
		nextObject = 2;
	}
}

void Game::addObject(SceneObject* o)
{
	if (nextObject == 1)
	{
		sceneObjects.push_front(o);
	}
	else if (nextObject == 2)
	{
		player = o;
		sceneObjects.push_back(o);
	}
	else
	{
		sceneObjects.push_back(o);
	}
}

void Game::spawnMushroom(int x, int y)
{
	sceneObjects.push_back(new Mushroom(this, x, y));
}

void Game::spawnCoin(int x, int y)
{
	sceneObjects.push_back(new Coin(this, x, y));
}

void Game::resetLevel()
{
	for (auto obj : sceneObjects)
	{
		if (obj != player && obj != tilemap)
		{
			delete obj; // POSIBLE FALLO -> NO SE BORRAN ENTIDADES ANTERIORES
		}
	}

	// reinicia mapoffset y lista de objetos
	nextObject = 2;
	mapOffset = 0;

	// recarga nivel
	loadLevel(level); // POSIBLE FALLO -> SE HACE LOAD DE ENTIDADES ANTERIORES + NUEVAS ??¿¿?
}


void Game::run()
{
	// Bucle principal del juego
	while (seguir) {
		// Marca de tiempo del inicio de la iteracion
		uint32_t inicio = SDL_GetTicks();

		update();       // Actualiza el estado de los objetos del juego
		render();       // Dibuja los objetos en la venta
		handleEvents(); // Maneja los eventos de la SDL

		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		// Duerme el resto de la duraci�n del frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
}

void
Game::render()
{
	// Cambia el color de fondo
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);

	SDL_RenderClear(renderer);

	tilemap->render(renderer);

	// Pinta los objetos del juego
	for (auto obj : sceneObjects) {
		obj->render(renderer);
	}

	// escena en pantalla 
	SDL_RenderPresent(renderer);
}

Collision Game::checkCollision(const SDL_Rect& rect, Collision::Target target) 
{
	Collision collision;

	for (SceneObject* obj : sceneObjects) 
	{
		collision = obj->hit(rect, target);

		if (collision.result != Collision::NONE) 
		{
			return collision;
		}
	}

	collision = tilemap->hit(rect, target);

	if (collision.result != Collision::NONE) 
	{
		return collision;
	}

	return { collision.NONE, 0, 0 };
}

void Game::endGame()
{
	seguir = false;
}


void
Game::update()
{
	// Instancia objetos segun su posicion en X
	while (nextObject < objectQueue.size() && 
		objectQueue[nextObject]->getXPos() < mapOffset + WIN_WIDTH + TILE_SIDE)
	{
		addObject(objectQueue[nextObject++]->clone());
	}

	for (auto obj : sceneObjects) {
		obj->update();
	}

	//tilemap->update();
}

void
Game::handleEvents()
{
	// Procesamiento de eventos
	SDL_Event evento;


	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT) {
			seguir = false;
		}
		else {
			player->handleEvent(evento);
		}
	}
}

void Game::playerHit()
{
	player->hit();
}

bool Game::getMarioImmunity()
{
	return player->getImmunity();
}