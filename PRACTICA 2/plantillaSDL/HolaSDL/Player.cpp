#include "Player.h"
#include "Game.h"

Player::Player(Game* game, int x, int y)
	: SceneObject(game, x, y, TILE_SIDE, TILE_SIDE, game->getTexture(Game::MARIO))
{
	game->setMarioState(0);

	lives = 3;

	marioSpeed = 6;
	onGround = false;
	jumping = false;

	frame = 0;
	walkFrame = 0;
	frameCounter = 0;
	flipSprite = true;
	flip = SDL_FLIP_HORIZONTAL;

	bgSpeed = 1;

	cout << "Mario (" << x << ", " << y << ")" << endl;
}

void Player::render(SDL_Renderer* renderer)
{
	_rect.x = _position.getX();

	// renderframe con flipeado
	if (game->getMarioState() == 0)
	{
		_rect.y = _position.getY();
		_rect.w = TILE_SIDE;
		_rect.h = TILE_SIDE;
		_texture->renderFrame(_rect, 0, frame, 0, nullptr, flip);
	}
	else
	{
		Texture* t = game->getTexture(Game::SUPERMARIO);

		_rect.y = _position.getY() - TILE_SIDE; // si no se sale del suelo
		_rect.w = t->getFrameWidth() * 2;
		_rect.h = t->getFrameHeight() * 2;
		t->renderFrame(_rect, 0, frame, 0, nullptr, flip);
	}

	//updateAnim();

	if (DEBUG) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128); // red
		SDL_RenderDrawRect(renderer, &_rect);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}

void Player::update()
{
	checkAlive();

	
	_speed.setY(_speed.getY() + GRAVITY);

	// Acelera la velocidad con la gravedad
	//if (_speed.getY() < SPEED_LIMIT)
	//	_speed += {0, GRAVITY};

	// Intenta moverse
	Collision collision = tryToMove(_speed, Collision::ENEMIES);

	// Si toca un objeto en horizontal
	if (collision.horizontal) {

		if (_speed.getX() > 0) {
			_position.setX(_position.getX() + _speed.getX() - collision.intersectionRect.w);
		}
		else {
			_position.setX(_position.getX() + _speed.getX() + collision.intersectionRect.w);
		}
	}
	else 
	{
		if (_speed.getX() > 0) // derecha
		{
			flip = SDL_FLIP_NONE;
			if (_position.getX() >= Game::WIN_WIDTH / 2) // si pasa la mitad de la pantalla
			{
				// mueve el fondo
				if (game->getMapOffset() <= MAX_MAP_OFFSET)
				{
					game->setMapOffset(game->getMapOffset() + BACKGROUND_SCROLL_SPEED * bgSpeed);
				}
			}
			else // mueve a mario
			{
				_position.setX(_position.getX() + _speed.getX());
			}

		}
		else if (_speed.getX() < 0)  // izquierda
		{
			flip = SDL_FLIP_HORIZONTAL;
			if (_position.getX() > 0) _position.setX(_position.getX() + _speed.getX());
		}
	}


	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical) { // si collision.vertical != 0
		cout << collision.result;
		if (_speed.getY() > 0)
		{
			_position.setY(_position.getY() + _speed.getY() - collision.intersectionRect.h);
			onGround = true;

		}
		else if (_speed.getY() < 0)
		{
			_position.setY(_position.getY() + _speed.getY() + collision.intersectionRect.h);
		}
		jumping = false;
		_speed.setY(0);
	}
	else 
	{
		_position.setY(_position.getY() + _speed.getY());
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
		frameCounter++;
		if (frameCounter >= 1)
		{
			frameCounter = 0;
			if (!immune) {
				walkFrame = (walkFrame + 1) % 4; // para que se repita el ciclo

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
			else
			{
				walkFrame = (walkFrame + 1) % 5; // para que se repita el ciclo

				if (walkFrame == 0 || walkFrame == 4) {
					frame = 2;
				}
				else if (walkFrame == 1) {
					frame = 3;
				}
				else if (walkFrame == 2) {
					frame = 4;
				}
				else if (walkFrame == 3) {
					frame = -1;
				}
			}
		}
	}
	else if (!onGround) {
		frame = 6;
	}
	else {
		frame = 0;
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
