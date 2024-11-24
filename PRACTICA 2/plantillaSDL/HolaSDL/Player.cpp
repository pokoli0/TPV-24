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

	bgSpeed = 1;

	cout << "Mario (" << x << ", " << y << ")" << endl;
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
		if (_position.getX() - game->getMapOffset() >= Game::WIN_WIDTH / 2)
		{
			if (game->getMapOffset() <= MAX_MAP_OFFSET) 
			{
				game->setMapOffset(game->getMapOffset() + _speed.getX() * bgSpeed);
			}
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
	if (_speed.getX() != 0 && onGround) // si se esta moviendo EN HORIZONTAL
	{
		_frameCounter++;
		if (_frameCounter >= 1)
		{
			_frameCounter = 0;
			if (!immune) {
				walkFrame = (walkFrame + 1) % 4; // para que se repita el ciclo

				if (walkFrame == 0 || walkFrame == 3) {
					_frame = 2;
				}
				else if (walkFrame == 1) {
					_frame = 3;
				}
				else if (walkFrame == 2) {
					_frame = 4;
				}
			}
			else
			{
				walkFrame = (walkFrame + 1) % 5; // para que se repita el ciclo

				if (walkFrame == 0 || walkFrame == 4) {
					_frame = 2;
				}
				else if (walkFrame == 1) {
					_frame = 3;
				}
				else if (walkFrame == 2) {
					_frame = 4;
				}
				else if (walkFrame == 3) {
					_frame = -1;
				}
			}
		}
	}
	else if (!onGround) {
		_frame = 6;
	}
	else {
		_frame = 0;
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

		case SDLK_PLUS:
			if (!fastMode) fastMode = true;
			else { fastMode = false; }
			break;

		case SDLK_d:
			if (!debugMode) debugMode = true;
			else {
				debugMode = false;
				system("cls");
			}
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
