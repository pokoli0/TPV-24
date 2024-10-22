#pragma once
#include "checkML.h"

#include <string>
#include <vector>
#include "Texture.h"
#include "Game.h"

using namespace std;
using uint = unsigned int;

class Game;

// dibuja el fondo y los obstaculos segun avanza el personaje
class Tilemap
{
private:
	Texture* background;
	Game* game;

	vector<vector<int>> indices;
	int x, y;

public:
	Tilemap();
	Tilemap(Game* g, vector<vector<int>> ind);
	~Tilemap();

	void render();
	void update();

	// detecta colisiones
	void hit();

};

