#ifndef GAME_H
#define GAME_H

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

#include "GameStateMachine.h"

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
class Game : private GameStateMachine
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
		LVL1,
		LVL2,
		EXIT,
		BG,
		RESUME,
		BACK,
		NUM_TEXTURES,  // Truco C++: número de texturas definidas
	};

	using GameStateMachine::pushState;
	using GameStateMachine::replaceState;

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


	/// ===== Estados =====

	GameStateMachine* gameStateMachine;


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
	void endGame();


	/// ===== Getters y Setters =====

	int getMarioState() const { return marioState; }
	void setMarioState(int s) { marioState = s; }

	int getPoints() const { return points; }
	void givePoints(int n) { points += n; }

	SDL_Renderer* getRender() const { return renderer; }

	GameStateMachine* getStateMachine() const { return gameStateMachine; }
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H 