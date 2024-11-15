#pragma once
#include "checkML.h"

#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"

#include "Collision.h"

class Goomba
{
private:
	Point2D<int> pos;

	SDL_Rect rect;

	Texture* texture;
	int frame;
	Game* game;

	int frameCounter;

	Point2D<int> dir;
	// true izda, false dcha
	bool flipSprite;
	int speed;
	bool isAlive;
	// para que no se muevan mientras no aparezcan en pantalla
	bool frozen;


public:

	Goomba();
	Goomba(Game* g, int x, int y);

	void render(SDL_Renderer* renderer);
	void update();
	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	void move();

	// compara con mapOffset para ver si el goomba aparece en pantalla
	// y asi poner frozen a true
	void checkFrozen();

};

