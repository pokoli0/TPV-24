#include "Player.h"
#include "Game.h"

Player::Player(Game* game, int x, int y)
	: SceneObject(game, x, y, TILE_SIDE, TILE_SIDE, game->getTexture(Game::MARIO))
{
	game->setMarioState(0);

	setScale(2);

	lives = 3;
	canMove = true;
	marioSpeed = 6;
	onGround = false;
	jumping = false;

	walkFrame = 0;
	_flipSprite = true;
	_flip = SDL_FLIP_NONE;

	cout << "Mario (" << x << ", " << y << ")" << endl;
}

void Player::render(SDL_Renderer* renderer)
{
		SceneObject::render(renderer);
		updateAnim();
}

void Player::update()
{
	checkAlive();

	if (_speed.getY() < SPEED_LIMIT) _speed += {0, GRAVITY};

	if(canMove)	collision = tryToMove(_speed, Collision::ENEMIES);
	else if(!canMove && _speed.getY() != 0) collision = tryToMove({0, _speed.getY()}, Collision::ENEMIES);

	if (collision.vertical) 
	{
		if (_speed.getY() > 0) 
		{
			onGround = true;
			jumping = false;
		}

		_speed.setY(0); // importante !!! @ marcos 
	}

	if (_speed.getX() > 0) 
	{
		_flip = SDL_FLIP_NONE;

		// Limites
		if (_position.getX() - game->getMapOffset() >= Game::WIN_WIDTH / 2 
			&& game->getMapOffset() <= MAX_MAP_OFFSET)
		{
			game->setMapOffset(game->getMapOffset() + _speed.getX());
		}
		canMove = true;
	}
	else if (_speed.getX() < 0)
	{
		_flip = SDL_FLIP_HORIZONTAL;

		if (_position.getX() - game->getMapOffset() < TILE_SIDE) canMove = false;
	}
}

Collision Player::hit(const SDL_Rect& region, Collision::Target target)
{
	return Collision();
}

SceneObject* Player::clone() const
{
	return nullptr;
}

void Player::checkAlive()
{
	if (_position.getY() >= MAX_HEIGHT && _isAlive) {
		cout << "sale por abajo" << endl;
		lives--;
		_isAlive = false;
	}

	if (lives == 0) {
		cout << "Game Lost" << endl;
		_isAlive = false;
	}

	//if (!_isAlive) resetPlayer();
}


void Player::resetPlayer()
{
}

void Player::updateAnim()
{
	if (_speed.getX() != 0 && onGround) 
	{
		_frameCounter++;
		if (_frameCounter >= 1) 
		{
			_frameCounter = 0;

			int cycleLength = immune ? 4 : 5;
			walkFrame = (walkFrame + 1) % cycleLength;

			// Asigna el frame correspondiente
			if (walkFrame == 0 || walkFrame == (cycleLength - 1)) {
				_frame = 2;
			}
			else if (walkFrame == 1) {
				_frame = 3;
			}
			else if (walkFrame == 2) {
				_frame = 4;
			}
			else if (immune && walkFrame == 3) {
				_frame = -1;
			}
		}
	}
	else if (!onGround) {
		_frame = 6; // Frame cuando está en el aire
	}
	else {
		_frame = 0; // Frame cuando está en reposo
	}
}

void Player::jump()
{
	if (!jumping && onGround)
	{
		onGround = false;
		jumping = true;

		_speed.setY(-30);
	}
}

void Player::handleEvent(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:
			_speed.setX(marioSpeed);
			break;

		case SDLK_LEFT:
			_speed.setX(-marioSpeed);
			break;

		case SDLK_SPACE:
			jump();
			break;
		case SDLK_r:
			resetPlayer();
			break;
		}
	}
	else if (e.type == SDL_KEYUP) // soltar teclas
	{
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:
			_speed.setX(0);
			break;

		case SDLK_LEFT:
			_speed.setX(0);
			break;

		}
	}
}

