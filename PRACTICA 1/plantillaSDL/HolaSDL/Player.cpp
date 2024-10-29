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

	pos = Point2D<int>(posx, posy);
	speed = 8;
	
	groundY = posy;
	jumping = false;
	jumpVelocity = 0;
	gravity = 1;

	texture = game->getTexture(Game::MARIO);
	
	frame = 0;
	walkFrame = 0;
	frameCounter = 0;
	flipSprite = false;

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
	rect.x = pos.getX();
	rect.y = pos.getY();
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

	// movimiento horizontal
	if (dir == 1) {
		flipSprite = false;
		if (pos.getX() >= Game::WIN_WIDTH / 2)
		{
			game->setMapOffset(offset + 5);
		}
		else {
			pos.setX(pos.getX() + speed);
		}
	}
	else if (dir == -1) {
		flipSprite = true;;
		if (pos.getX() > TILE_SIDE) {
			pos.setX(pos.getX() - speed);
		}
	}

	// salto
	if (jumping) {
		pos.setY(pos.getY() + jumpVelocity);
		jumpVelocity += gravity; // Aumenta velocidad hacia abajo

		// Comprobamos si ha alcanzado el suelo
		if (pos.getY() >= groundY) {
			pos.setY(groundY);
			jumping = false;
			jumpVelocity = 0;
		}
	}
}

void Player::jump()
{
	if (!jumping) 
	{
		cout << "Salto" << endl;
		jumping = true;
		jumpVelocity = -15; 
	}

}

void Player::updateAnim()
{
	if (dir != 0) // si se esta moviendo
	{
		frameCounter++;
		if (frameCounter >= 1){		
			frameCounter = 0;
			walkFrame = (walkFrame + 1) % 4;

			if (walkFrame == 0 || walkFrame == 3) {
				frame = 2;
			}
			else if (walkFrame == 1) {
				frame = 3;
			}
			else if (walkFrame == 2) {
				frame = 4;
			}
		}
	}
	else if (jumping) {
		frame = 6;
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
