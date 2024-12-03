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
	//mapOffset(4080), // para probar el lift
	points(0)
{
	// Inicializa la SDL
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

	// Carga las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i)
		textures[i] = new Texture(renderer,
			(textureRoot + textureSpec[i].name).c_str(),
			textureSpec[i].numRows,
			textureSpec[i].numColumns);

	//Crea los objetos del juego
	tilemap = new TileMap(this, "../assets/maps/world2.csv");
	//sceneObjects.push_back(tilemap);

	//sceneObjects.push_back(new TileMap(this, "../assets/maps/world2.csv"));

	//sceneObjects.push_back(new InfoBar(this));

	loadObjectMap("../assets/maps/world2.txt");
	//loadObjectMap("../assets/maps/world2.txt");

	marioState = 0; // empieza mario chiquito
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

void Game::loadObjectMap(const string& mapFile)
{
	// Carga el mapa
	ifstream file(mapFile);

	if (!file.is_open()) {
		throw string("fichero de mapa worldX.txt no encontrado");
	}

	// Leemos el mapa l�nea a l�nea para evitar acarreo de errores
	// y permitir extensiones del formato
	string line;

	getline(file, line); // lectura primera linea

	// Usamos un stringstream para leer la l�nea como si fuera un flujo
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
			//player = new Player(this, 4366, 300); // para probar el lift
			player = new Player(this, x, y);
			sceneObjects.push_back(player);
			break;
		case 'B':
			sceneObjects.push_back(new Block(this, x, y, atrib, accion));
			break;
		case 'G':
			sceneObjects.push_back(new Goomba(this, x, y));
			break;
		case 'K':
			sceneObjects.push_back(new Koopa(this, x, y));
			break;
		case 'L':
			sceneObjects.push_back(new Lift(this, x, y, sp));
			break;
		case 'C':
			sceneObjects.push_back(new Coin(this, x, y));
			break;
		}		
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
	auto it = sceneObjects.begin();

	while (it != sceneObjects.end()) {
		SceneObject* obj = *it;

		if (obj == player || obj == tilemap) {
			++it;
		}
		else {
			delete obj; // Eliminar el objeto
			//it = sceneObjects.erase(it); // Eliminar de la lista y avanzar el iterador
		}
	}

	nextObject = 0;

	for (SceneObject* obj : objectQueue) {
		sceneObjects.push_back(obj->clone());
	}
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


void
Game::update()
{
	//if (nextObject < objectQueue.size()) 
	//{
	//	SceneObject* obj = objectQueue[nextObject];
	//	SDL_Rect objRect = obj->getRenderRect();

	//	// si aparece en pantalla clonar
	//	if (objRect.x + objRect.w > mapOffset && objRect.x < mapOffset + WIN_WIDTH && 
	//		objRect.y + objRect.h > 0 && objRect.y < WIN_HEIGHT) 
	//	{
	//		sceneObjects.push_back(obj->clone());
	//		nextObject++;
	//	}
	//}

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