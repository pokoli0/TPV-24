#pragma once
#include "checkML.h"

// Biblioteca estándar de C++
#include <array>

// Biblioteca SDL
#include <SDL.h>

// Nuestras clases
#include "Texture.h"

using uint = unsigned int;

//
// Clase que representa el juego y controla todos sus aspectos
//
class Game
{
public:
	// Identificadores de las texturas
	enum TextureName {
		BACKGROUND,
		DOG,
		HELICOPTER,
		NUM_TEXTURES,  // Truco C++: número de texturas definidas
	};

private:
	// Ventana de la SDL (se destruirá en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;

	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> textures;
	// Interruptor para terminar el juego
	bool seguir;

	// desplazamiento del mapa
	int mapOffset;

	// Objetos del juego
	//Dog* perro;

public:
	// bucle principal del juego
	void run();

	void update();
	void render() const;
	void handleEvents();

	Texture* getTexture(TextureName name) const;

	// Constante globales
	static constexpr uint WIN_WIDTH = 800;
	static constexpr uint WIN_HEIGHT = 600;
	static constexpr uint FRAME_RATE = 50;

	// aqui se cargan las texturas y se guardan en el array textures
	Game();
	~Game();

	int getMapOffset() { return mapOffset; }

	// se encarga de invertir la direccion de goombas, koopas y champis ?
	void collides();

	// leera lineas completas con getline para pasarselo al constructor del objeto,
	// construira un flujo temporal istringstream ?¿?¿
	void loadMap();
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

