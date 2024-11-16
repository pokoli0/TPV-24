#pragma once
#include "checkML.h"

#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"

#include "Collision.h"

class Mushroom
{
private:
	Point2D<int> pos;
	Point2D<int> speed;
	int xSpeed;

	bool onGround;

	SDL_Rect rect;

	Texture* texture;
	int frame;
	Game* game;

	int frameCounter;

	bool isAlive;



public:

	Mushroom();
	Mushroom(Game* g, int x, int y);

	void render(SDL_Renderer* renderer);
	void update();

	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	void checkAlive();

	// getters
	bool getAlive() { return isAlive; }

};

