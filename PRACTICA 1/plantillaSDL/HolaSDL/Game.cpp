#include <string>

#include "Game.h"
#include <iostream>
#include <fstream>

using namespace std;

// Formato de la especificaciÃ³n de una textura
struct TextureSpec
{
	const char* name;	// Ruta del archivo
	uint numColumns;	// Num de frames por fila
	uint numRows;		// Num de frames por columna
};

// Directorio raiz de los archivos de textura
const string textureRoot = "../assets/imgs/";

// Especificacion de las texturas del juego
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"background.png", 9, 7},
	{"mario.png", 12, 1},
};

Game::Game()
 : seguir(true)
{
	// Inicializa la SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL",
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
	//perro = new Dog(this, -textures[DOG]->getFrameWidth(), 390);
}

Game::~Game()
{
	// Elimina los objetos del juego
	//delete perro;

	// Elimina las texturas
	for (Texture* texture : textures)
		delete texture;

	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::loadMap(string fichero)
{
	ifstream f; 
	f.open(fichero);
	if (!f.is_open()) {
		throw string("fichero de mapa no encontrado");
	}
	else {
		std::string linea;
		std::vector<vector<int>> matriz;

		while (std::getline(f, linea)) {
			std::istringstream stream(linea);
			std::string valor;
			std::vector<int> fila;


			// Leer cada valor separado por coma
			while (std::getline(stream, valor, ',')) {
				std::istringstream convertir(valor); // Crear un istringstream para la conversión
				int num;
				convertir >> num; // Convertir el string a int
				fila.push_back(num); // Agregar el número a la fila
			}

			matriz.push_back(fila); // Agregar la fila a la matriz
		}
		
		tilemap = new Tilemap(this, matriz);
	}

	f.close();
}

void Game::run()
{
	loadMap("../assets/maps/world1.csv");

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
	SDL_RenderClear(renderer);

	// Pinta los objetos del juego
	//textures[BACKGROUND]->render();
	//perro->render();
	tilemap->render();
	// escena en pantalla 
	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	// Actualiza los objetos del juego
	//perro->update();
}

void
Game::handleEvents()
{
	// Procesamiento de eventos
	SDL_Event evento;

	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT)
			seguir = false;
		else if (evento.type == SDL_KEYDOWN) {
			//perro->handleEvent(evento);
		}
	}
}
