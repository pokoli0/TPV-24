#pragma once
#include "checkML.h"

// Biblioteca estándar de C++
#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// Biblioteca SDL
#include <SDL.h>

// Nuestras clases
#include "Texture.h"
#include "Tilemap.h"
#include "Player.h"
#include "Block.h"
#include "Goomba.h"
#include "Koopa.h"

#include "Collision.h"

class Block;
class Tilemap;
class Player;
class Goomba;
class Koopa;

using uint = unsigned int;
using namespace std;


static constexpr int TILE_SIDE = 32;  // constantes estáticas en Game
static constexpr int WINDOW_WIDTH = 18;
static constexpr int WINDOW_HEIGHT = 16;

static constexpr int MAX_MAP_OFFSET = 6150;
static constexpr int BACKGROUND_SCROLL_SPEED = 5;

static constexpr int OBSTACLE_THRESHOLD = 4;

//
// Clase que representa el juego y controla todos sus aspectos
//
class Game
{
public:
	// Identificadores de las texturas
	enum TextureName {
		BACKGROUND,
		MARIO,
		SUPERMARIO,
		BLOCKS,
		GOOMBA,
		KOOPA,
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

	// coordenada x del extremo izquierdo de la vista
	int mapOffset;

	// Objetos del juego
	Tilemap* tilemap = nullptr;
	Player* player = nullptr;
	Block* block = nullptr;
	vector<Block*> blockGroup;
	Goomba* goomba = nullptr;
	vector<Goomba*> goombaGroup;
	Koopa* koopa = nullptr;
	vector<Koopa*> koopaGroup;

public:
	// bucle principal del juego
	void run();

	/*
	Game tiene acceso a todos los objetos del juego, así que puede preguntarle a cada uno de ellos 
	(con el método hit) si colisiona con el rectángulo.

	@param rect: objeto que se va a mover y del que queremos comprobar colisiones
	@param fromPlayer: origen de colision es mario (true) o un enemigo (false)

	@return objeto colision con toda la informacion estructurada
	*/
	Collision checkCollision(const SDL_Rect& rect, bool fromPlayer);

	void update();
	void render() const;
	void handleEvents();

	Texture* getTexture(TextureName name) const;
	array<Texture*, NUM_TEXTURES> getTexturesArray() const { return textures; }

	// Constante globales
	static constexpr uint WIN_WIDTH = TILE_SIDE * WINDOW_WIDTH;
	static constexpr uint WIN_HEIGHT = TILE_SIDE * WINDOW_HEIGHT;
	static constexpr uint FRAME_RATE = 50;

	// aqui se cargan las texturas y se guardan en el array textures
	Game();
	~Game();

	void loadObjectMap();

	// se encarga de invertir la direccion de goombas, koopas y champis ?
	void collides();

	/// GETTERS --------------------------------
	int getMapOffset() { return mapOffset; }
	void setMapOffset(int m) { mapOffset = m; }
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

