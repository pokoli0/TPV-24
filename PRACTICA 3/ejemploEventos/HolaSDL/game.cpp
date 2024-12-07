#include "game.h"

#include "bola.h"
#include "button.h"
#include "counter.h"

using namespace std;

constexpr uint32_t FRAME_RATE = 10;

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Eventos con SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == nullptr || renderer == nullptr)
		throw "Error cargando SDL"s;

	bola = new Bola(this);
	boton = new Button(this);
	counter = new Counter(this);

	boton->addClickListener(bola);
	boton->addClickListener(counter);
}

Game::~Game()
{
	delete bola;
	delete boton;
	delete counter;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void
Game::update()
{
	bola->update();
	boton->update();
}

void
Game::render() const
{
	SDL_RenderClear(renderer);
	boton->render();
	bola->render();
	counter->render();
	SDL_RenderPresent(renderer);
}

void
Game::run()
{
	exit = false;

	while (!exit) {
		uint32_t ticks0 = SDL_GetTicks();
		render();
		update();
		handleEvents();

		uint32_t ticks = SDL_GetTicks();
		if (ticks - ticks0 < FRAME_RATE)
			SDL_Delay(FRAME_RATE + ticks0 - ticks);
	}
}

void
Game::handleEvents()
{
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			exit = true;
		else
			// Emite el evento para todos los subscriptores
			emit(event);
	}
}

void
Game::connect(SDLEventCallback cb)
{
	callbacks.push_back(cb);
}

void
Game::emit(const SDL_Event& event) const
{
	// Llama a todas las funciones registradas
	for (const SDLEventCallback& callback : callbacks)
		callback(event);
}
