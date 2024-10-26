#include "Player.h"

Player::Player()
{
}

Player::Player(Game* g, int posx, int posy)
{
	game = g;
	actualAspect = MARIO;
	lives = 3;
	dir = 1;

	x = posx;
	y = posy;

	texture = game->getTexture(Game::MARIO);

	cout << "Mario" << endl;
}

Player::~Player()
{
	//texture = nullptr;
	delete texture;
}

void Player::render()
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();

	// fila 0 (no hay mas filas)
	// columna 0 - frame 0
	texture->renderFrame(rect, 0, 0);

}

void Player::update()
{
	// movimiento

	//...

	render();
}
