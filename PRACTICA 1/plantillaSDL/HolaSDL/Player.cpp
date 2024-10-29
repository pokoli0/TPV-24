#include "Player.h"

Player::Player()
{
}

Player::Player(Game* g, int posx, int posy)
{
	game = g;
	actualAspect = MARIO;
	lives = 3;
	dir = 0;

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
	int offset = game->getMapOffset();

	// movimiento
	if (dir == 1) {
		if (x >= Game::WIN_WIDTH / 2) {
			game->setMapOffset(offset + 5);
		}
		else {
			x = x + 5;
		}
	}
	else if (dir == -1) {
		if (x > TILE_SIDE) {
			x = x - 5;
		}
	}
}

void Player::handleEvents(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			dir = 1;
			break;

		case SDLK_LEFT:
			dir = -1;
			break;

		case SDLK_SPACE:
			cout << "salto" << endl;
			break;
		}
	}
	else if (event.type == SDL_KEYUP) {
		dir = 0;
		cout << "suelto tecla" << endl;
	}
}
