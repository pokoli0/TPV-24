#include "Player.h"

Player::Player()
{
}

Player::Player(Game* g)
{
	game = g;
	actualAspect = MARIO;
	lives = 3;
	dir = 1;

	x = 20;
	y = 20;

	texture = game->getTexture(Game::MARIO);
}

Player::~Player()
{
	//texture = nullptr;
	//delete texture;
}

void Player::render()
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();

	texture->renderFrame(rect, 0, texture->getNumColumns());

	cout << "render player" << endl;
}
