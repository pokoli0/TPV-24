#include "Game.h"
#include "Block.h"
// Formato de la especificaciÃ³n de una textura
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
};

Game::Game()
 : seguir(true), mapOffset(1)
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
	tilemap = new Tilemap(this, "../assets/maps/world1.csv");

	loadObjectMap();
}

Game::~Game()
{
	// Elimina los objetos del juego
	delete tilemap;
	delete player;
	for (int i = 0; i < blockGroup.size(); i++)
	{
		delete blockGroup[i];
	}
	for (int i = 0; i < goombaGroup.size(); i++)
	{
		delete goombaGroup[i];
	}
	for (int i = 0; i < koopaGroup.size(); i++)
	{
		delete koopaGroup[i];
	}

	// Elimina las texturas
	for (Texture* texture : textures)
		delete texture;

	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::loadObjectMap()
{
	const char* DEFAULT_MAP = "../assets/maps/world1.txt";

	// Carga el mapa
	ifstream file(DEFAULT_MAP);

	if (!file.is_open()) {
		throw string("fichero de mapa worldX.txt no encontrado");
	}

	// Leemos el mapa línea a línea para evitar acarreo de errores
	// y permitir extensiones del formato
	string line;

	while (getline(file, line)) {
		// Usamos un stringstream para leer la línea como si fuera un flujo
		stringstream lineStream(line);

		char tipo, atrib, accion;
		int x, y;
		lineStream >> tipo >> x >> y >> atrib >> accion;
		
		// conversion
		x = x * TILE_SIDE;
		y = y * TILE_SIDE - TILE_SIDE;

		switch (tipo) {
		case 'M':
			player = new Player(this, 32, 300); // 32, 32*13
			break;
		case 'B':
			block = new Block(this, x, y, atrib, accion);
			blockGroup.push_back(block);
			break;
		case 'G':
			goomba = new Goomba(this, x, y);
			goombaGroup.push_back(goomba);
			break;
		case 'K':
			koopa = new Koopa(this, x, y);
			koopaGroup.push_back(koopa);
			break;

		}
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

		// Duerme el resto de la duración del frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
}

void
Game::render() const
{
	// Cambia el color de fondo
	SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);

	SDL_RenderClear(renderer);

	// Pinta los objetos del juego
	tilemap->render(renderer);
	player->render(renderer);

	for (int i = 0; i < blockGroup.size(); i++)
	{
		blockGroup[i]->render();
	}

	for (int i = 0; i < goombaGroup.size(); i++)
	{
		goombaGroup[i]->render();
	}

	for (int i = 0; i < koopaGroup.size(); i++)
	{
		koopaGroup[i]->render();
	}

	// escena en pantalla 
	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	// Actualiza los objetos del juego
	tilemap->update();
	player->update();

	for (int i = 0; i < blockGroup.size(); i++)
	{
		blockGroup[i]->update();
	}

	for (int i = 0; i < goombaGroup.size(); i++)
	{
		goombaGroup[i]->update();
	}

	for (int i = 0; i < koopaGroup.size(); i++)
	{
		koopaGroup[i]->update();
	}
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
			player->handleEvents(evento);
		}
	}
}

Collision Game::checkCollision(const SDL_Rect& rect, bool fromPlayer) 
{
	Collision col;

	//tilemap
	col = tilemap->hit(rect, fromPlayer);


	return col;
}
