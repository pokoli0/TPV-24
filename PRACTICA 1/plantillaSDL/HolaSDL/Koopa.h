#pragma once
#include "checkML.h"

#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"
#include "Player.h"
#include "Collision.h"
class Koopa
{
private:
	Point2D<int> pos;
	Point2D<int> speed;
	int xSpeed;

	bool onGround;

	SDL_Rect rect;
	SDL_RendererFlip flip;

	Texture* texture;
	Game* game;
	int frame;
	int frameCounter;
	int koopaFrame;

	bool isAlive;
	bool frozen;


public:

	Koopa();
	Koopa(Game* g, int x, int y);

	void render(SDL_Renderer* renderer);
	void update();

	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	void updateAnim();

	// mira si se ha salido del mapa y pone isAlive a false en ese caso
	void checkAlive();

	// getters
	bool getAlive() { return isAlive; }

};

