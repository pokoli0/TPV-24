#pragma once
#include "checkML.h"

#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"

#include "Collision.h"

class Goomba
{
private:
	// para que no se muevan mientras no aparezcan en pantalla
	bool frozen = true;

	Point2D<int> pos;
	Point2D<int> speed;
	int xSpeed;

	bool onGround;

	SDL_Rect rect;

	Texture* texture;
	int frame;
	Game* game;

	int frameCounter;




public:
	bool isAlive;
	Goomba();
	Goomba(Game* g, int x, int y);

	void render(SDL_Renderer* renderer);
	void update();
	void Alive();

	Collision hit(const SDL_Rect& rect, bool fromPlayer);
	// getters
	bool getAlive() { return isAlive; }
};

