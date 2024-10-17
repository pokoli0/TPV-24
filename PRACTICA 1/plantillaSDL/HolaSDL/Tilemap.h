#pragma once

#include "Texture.h"

// dibuja el fondo y los obstaculos segun avanza el personaje
class Tilemap
{
private:
	Texture* texture;

public:
	Tilemap();
	//Tilemap( ... );
	~Tilemap();

	void render();
	void update();

	// detecta colisiones
	void hit();

};

