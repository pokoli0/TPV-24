#include "Player.h"
#include "Game.h"

Player::Player(Game* game, int x, int y)
	: SceneObject(game, x, y, TILE_SIDE, TILE_SIDE, game->getTexture(Game::MARIO))
{
	game->setMarioState(0);

	initPos = Point2D<double>(x, y);

	setScale(2);

	lives = 3;
	immune = false;

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
	_texture = game->getMarioState() == 0 ? game->getTexture(Game::MARIO) : game->getTexture(Game::SUPERMARIO);

	_rect.x = _position.getX() - game->getMapOffset();
	
	if (_texture == game->getTexture(Game::SUPERMARIO))
	{
		_rect.y = _position.getY() - (_height * _scale); // el rect.y de mario grande empieza mas abajo!
		//_rect.h = _texture->getFrameHeight();
	}
	else
	{
		_rect.y = _position.getY() - _height;
	}

	_rect.h = _texture->getFrameHeight() * _scale;
	_rect.w = _texture->getFrameWidth() * _scale;

	_texture->renderFrame(_rect, 0, _frame, 0, nullptr, _flip);

	if (DEBUG) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 128);
		SDL_RenderDrawRect(renderer, &_rect);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}

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

		_speed.setY(0);
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

	if (!onGround) 
	{
		SDL_Rect r = getCollisionRect();
		r.y += 1;
		if (game->checkCollision(r, Collision::ENEMIES).result == Collision::OBSTACLE) {
			_speed.setY(0);
			onGround = true;
		}
	}

	if (immune)
	{
		temp++;
		if (temp >= immuneTime)
		{
			temp = 0;
			immune = false;
		}
	}

	finishLevel();

}

Collision Player::hit(const SDL_Rect& region, Collision::Target target)
{
	return Collision{};
}

void Player::hit()
{
	if (game->getMarioState() == 1 && !immune)
	{
		game->setMarioState(0);
	}
	else if (game->getMarioState() == 0 && !immune)
	{
		lives--;
		_isAlive = false;

		resetPlayer();
	}
	immune = true;
}

SceneObject* Player::clone() const
{
	return new Player(*this);
}

void Player::checkAlive()
{
	if (_position.getY() >= MAX_HEIGHT && _isAlive) 
	{
		lives--;
		_isAlive = false;
	}

	if (lives == 0) {
		cout << "Game Lost" << endl;
		_isAlive = false;
		lives = 3;
	}

	if (!_isAlive) resetPlayer();
}


void Player::resetPlayer()
{
	game->setMapOffset(0);
	_position = initPos;

	_isAlive = true;
	game->setMarioState(0);
}

void Player::finishLevel()
{
	if (_position.getX() >= winPosition &&
		game->getLevel() == 1)
	{
		_speed.setX(0);
		cout << "FINAL" << endl;
		game->setLevel(game->getLevel() + 1);
		cout << "level" << game->getLevel() << endl;
		game->setGameWon(true);

		if (game->getLevel() < game->getLastLevel() + 1)
		{
			game->resetLevel();

		}
		else
		{
			game->endGame();			
		}
	}
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
		_frame = 6; // Frame cuando est� en el aire
	}
	else {
		_frame = 0; // Frame cuando est� en reposo
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
		case SDLK_i:
			cout << "MARIO POS (" << _position.getX() << ", " << _position.getY() << ")" << endl;
			cout << "MAP OFFSET (" << game->getMapOffset() << ")" << endl;
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

