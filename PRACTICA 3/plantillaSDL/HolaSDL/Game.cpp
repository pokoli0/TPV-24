#include "checkML.h"

#include "Game.h"

#include "MainMenuState.h"

using namespace std;

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
				{"nivel1.png", 1, 1},
				{"nivel2.png", 1, 1},
				{"salir.png", 1, 1},
				{"portada.png", 1, 1},
				{"continuar.png", 1, 1},
				{"volver.png", 1, 1},
};

Game::Game()
	: seguir(true),
	points(0),
	marioState(0),
	gameStateMachine(new GameStateMachine())
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

	// Estados
	GameState* mainMenu = new MainMenuState(this);
	gameStateMachine->pushState(mainMenu);

}

Game::~Game()
{
	delete gameStateMachine;

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

		// Duerme el resto de la duraci�n del frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
}

void
Game::render()
{
	SDL_RenderClear(renderer);

	gameStateMachine->render(renderer);

	// presenta la escena en pantalla
	SDL_RenderPresent(renderer);

	// escena en pantalla 
	SDL_RenderPresent(renderer);
}

void Game::endGame()
{
	seguir = false;
}

void
Game::update()
{
	gameStateMachine->update();
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
			gameStateMachine->handleEvent(evento);
			//player->handleEvent(evento); // ESTO ASI NO PERO SE INVESTIGA JEJE
		}
	}
}
