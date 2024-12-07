#ifndef GAME_H
#define GAME_H
#include "checkML.h"

#include <functional>  // para std::function
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

using uint = unsigned int;

// Tipo de función que recibe un evento SDL por referencia
using Callback = std::function<void(const SDL_Event&)>;

// Declaraciones anticipadas
class Bola;
class Button;
class Counter;

class Game {
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool exit;

	Bola* bola;
	Button* boton;
	Counter* counter;

	void update();
	void render() const;
	void handleEvents();

	// Lista de funciones a llamar cuando se produzca un evento
	std::vector<Callback> callbacks;
	void emit(const SDL_Event &event) const;

public:
	static constexpr uint WIN_WIDTH = 800;
	static constexpr uint WIN_HEIGHT = 600;

	Game();
	~Game();

	void run();
	SDL_Renderer* getRenderer();

	// Se suscribe a los eventos SDL del juego
	void connect(Callback cb);
};

inline SDL_Renderer*
Game::getRenderer()
{
	return renderer;
}

#endif // GAME_H
