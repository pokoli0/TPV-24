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

	// -1 izda, 1 dcha
	int dir;
	// true izda, false dcha
	bool flipSprite;
	int speed;
	int backgroundScrollSpeed;

public:

	Koopa();
	Koopa(Game* g, int x, int y);

	void render();
	void update();
	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	void move();

};

