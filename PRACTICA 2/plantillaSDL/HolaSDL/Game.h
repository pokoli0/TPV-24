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
#include "Collision.h"

#include "GameList.h"
#include "SceneObject.h"

#include "InfoBar.h"

#include "TileMap.h"
#include "Player.h"

#include "Goomba.h"
#include "Koopa.h"
#include "Block.h"

#include "Mushroom.h"
#include "Coin.h"

#include "Lift.h"

#include "SDLError.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"

using uint = unsigned int;
using namespace std;


constexpr int TILE_SIDE = 32;  // constantes estáticas en Game
constexpr int WINDOW_WIDTH = 18;
constexpr int WINDOW_HEIGHT = 16;

constexpr int MAX_MAP_OFFSET = 6150;
constexpr int MAX_HEIGHT = 475 + 32;

constexpr int BACKGROUND_SCROLL_SPEED = 5;

constexpr int OBSTACLE_THRESHOLD = 4;

constexpr int GRAVITY = 3;
constexpr int SPEED_LIMIT = 10;

constexpr bool DEBUG = false;


//
// Clase que representa el juego y controla todos sus aspectos
//
class Game
{
public:

	// Constante globales
	static constexpr uint WIN_WIDTH = TILE_SIDE * WINDOW_WIDTH;
	static constexpr uint WIN_HEIGHT = TILE_SIDE * WINDOW_HEIGHT;
	static constexpr uint FRAME_RATE = 50;

	// Identificadores de las texturas
	enum TextureName {
		BACKGROUND,
		MARIO,
		SUPERMARIO,
		BLOCKS,
		GOOMBA,
		KOOPA,
		MUSHROOM,
		COIN,
		LIFT,
		NUMBERS,
		NUM_TEXTURES,  // Truco C++: número de texturas definidas
	};

private:
	/// ===== SDL =====

	// Ventana de la SDL (se destruirá en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;


	/// ===== Juego =====

	// Interruptor para terminar el juego
	bool seguir;

	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> textures;

	// colores del fondo del nivel
	int r, g, b;

	// coordenada x del extremo izquierdo de la vista
	int mapOffset;

	// nivel actual del juego
	int level;

	// ultimo nivel
	int lastLevel;

	bool gameWon;

	/// --- SceneObjects ---

	Player* player = nullptr;
	SceneObject* tilemap = nullptr;

	// Objetos del juego
	GameList<SceneObject> sceneObjects;

	// vamos extrayendo objetos de la cola segun vaya avanzando el nivel
	std::vector<SceneObject*> objectQueue;

	// indice para indicar el siguiente objeto a instanciar
	int nextObject; 


	/// ===== Otros =====
	
	int marioState; // 0: mario, 1: supermario
	int points;

public:
	// bucle principal del juego
	void run();

	void update();
	void render();
	void handleEvents();

	Texture* getTexture(TextureName name) const;
	array<Texture*, NUM_TEXTURES> getTexturesArray() const { return textures; }

	Game();
	~Game();


	/// ===== Gestion del nivel =====

	void loadLevel(int level); // Carga el nivel

	void loadObjectMap(const string& mapFile); // Carga los objs del nivel

	void resetLevel();

	void endGame();

	/// ===== Gestion del juego =====

	// Lo llama cada objeto en su update y su caja de colision.
	// Itera sobre los objetos del juego llamando a sus metodos hit.
	// Si ha habido una colision(detectada por hit), interrumpe la busqueda y la devuelve.
	Collision checkCollision(const SDL_Rect& rect, Collision::Target target);

	// spawnea mushroom encima del bloque 
	void spawnMushroom(int x, int y);
	void spawnCoin(int x, int y);

	// llama al hit del mario
	void playerHit();


	/// ===== Getters y Setters =====

	int getMapOffset() const { return mapOffset; }
	void setMapOffset(int m) { mapOffset = m; }

	int getMarioState() const { return marioState; }
	void setMarioState(int s) { marioState = s; }

	int getPoints() const { return points; }
	void givePoints(int n) { points += n; }

	bool getMarioImmunity();

	SDL_Renderer* getRender() { return renderer; }

	int getLastLevel() const { return lastLevel; }

	int getLevel() { return level; }
	void setLevel(int n) { level = n; }

	void setGameWon(bool w) { gameWon = w; }
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

