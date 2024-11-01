#pragma once
#include "checkML.h"

#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"

class Koopa
{
private:
	Point2D<int> pos;

	Texture* texture;
	int frame;
	Game* game;

	int frameCounter;

public:

	Koopa();
	Koopa(Game* g, int x, int y);

	void render();
	void update();
	void hit();

};

