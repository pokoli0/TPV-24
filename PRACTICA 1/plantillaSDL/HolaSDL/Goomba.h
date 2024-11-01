#pragma once
#include "checkML.h"

#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"

class Goomba
{
private:
	Point2D<int> pos;

	Texture* texture;
	int frame;
	Game* game;

	int frameCounter;

public:

	Goomba();
	Goomba(Game* g, int x, int y);

	void render();
	void update();
	void hit();

};

