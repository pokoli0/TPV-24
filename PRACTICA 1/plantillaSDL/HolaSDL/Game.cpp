#include <string>

#include "Game.h"
#include <iostream>
#include <fstream>

using namespace std;

// Formato de la especificaci√≥n de una textura
struct TextureSpec
{
	const char* name;	// Ruta del archivo
	uint numColumns;	// Num de frames por fila
	uint numRows;		// Num de frames por columna
};

// Directorio raiz de los archivos de textura
const string textureRoot = "../assets/imgs/";

// Especificacion de las texturas del juego
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec
{
	TextureSpec	{"background.png", 9, 7},
				{"mario.png", 12, 1},
};

Game::Game()
 : seguir(true), mapOffset(0)
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
	player = new Player(this, 32, 32 * 13);
}

Game::~Game()
{
	// Elimina los objetos del juego
	delete tilemap;
	delete player;

	// Elimina las texturas
	for (Texture* texture : textures)
		delete texture;

	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
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

		// Duerme el resto de la duraciÛn del frame
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
	tilemap->render();
	player->render();

	// escena en pantalla 
	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	// Actualiza los objetos del juego
	tilemap->update();
	player->update();
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
		else if (evento.type == SDL_KEYDOWN) {
			if (evento.key.keysym.sym == SDLK_RIGHT)
			{
				player->handleEvents(1);
			}
			else if (evento.key.keysym.sym == SDLK_LEFT)
			{
				player->handleEvents(-1);
			}
		}
		else if (evento.type == SDL_KEYUP){
			player->handleEvents(0);
		}
	}
}
