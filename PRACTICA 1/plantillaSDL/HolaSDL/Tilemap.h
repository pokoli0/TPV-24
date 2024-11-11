#pragma once
#include "checkML.h"

#include <string>
#include <vector>
#include <sstream> 
#include <iostream>
#include <fstream>

#include "Texture.h"
#include "Game.h"

#include "Collision.h"

using namespace std;
using uint = unsigned int;

class Game;

// dibuja el fondo y los obstaculos segun avanza el personaje
class Tilemap
{
private:
	Texture* texture = nullptr;
	Texture* background = nullptr;
	Game* game = nullptr;

	SDL_Rect rect;

	vector<vector<int>> indices;
	int x, y;

public:
	Tilemap();
	Tilemap(Game* g, string f);
	~Tilemap();
	
	// leera lineas completas con getline para pasarselo al constructor del objeto
	void loadTilemap(string fichero);
	void renderTilemap();

	void render();
	// mueve el fondo
	void update();

	// detecta colisiones
	Collision hit(const SDL_Rect& rect, bool fromPlayer);

};

