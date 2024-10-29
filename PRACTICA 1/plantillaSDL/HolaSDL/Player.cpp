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
	
	frame = 0;

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
	//texture->renderFrame(rect, 0, frame);

	SDL_RendererFlip flip;
	if (flipSprite) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	else {
		flip = SDL_FLIP_NONE;
	}

	texture->renderFrame(rect, 0, frame, 0, nullptr, flip);
}

void Player::update()
{
	move();

	updateAnim();
}

void Player::move()
{
	int offset = game->getMapOffset();

	// movimiento
	if (dir == 1) {
		flipSprite = false;
		if (x >= Game::WIN_WIDTH / 2) {
			game->setMapOffset(offset + 5);
		}
		else {
			x = x + 5;
		}
	}
	else if (dir == -1) {
		flipSprite = true;;
		if (x > TILE_SIDE) {
			x = x - 5;
		}
	}
}

void Player::jump()
{
	cout << "salto" << endl;


}

void Player::updateAnim()
{
	if (dir != 0) // si se esta moviendo
	{
		frameTimer++;
		if (frameTimer >= 2) { 
			frameTimer = 0;
			walkFrame = (walkFrame + 1) % 4;  // Ciclo 0,1,2,3, y luego se reinicie 

			if (walkFrame == 0 || walkFrame == 3) frame = 2;
			else if (walkFrame == 1) frame = 3;
			else if (walkFrame == 2) frame = 4;
		}
	}
	else {
		frame = 0;
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
			jump();
			break;
		}
	}
	else if (event.type == SDL_KEYUP) {
		dir = 0;
	}
}
