#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* game, int x, int y, Texture* t)
	: SceneObject(game, x, y, TILE_SIDE, TILE_SIDE, t)
{

}

void Enemy::render(SDL_Renderer* renderer)
{
	_rect.x = _position.getX() - game->getMapOffset();
	_rect.y = _position.getY();
	_rect.w = _texture->getFrameWidth() * 2;
	_rect.h = _texture->getFrameHeight() * 2;

	_texture->renderFrame(_rect, 0, _frame, 0, nullptr, _flip);

	if (DEBUG) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 128);
		SDL_RenderDrawRect(renderer, &_rect);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}

void Enemy::update()
{
	checkAlive();

	if (_position.getX() - _texture->getFrameWidth() * (TILE_SIDE + 5) < game->getMapOffset()) frozen = false;
	
	if (!frozen) 
	{
		// Acelera la velocidad con la gravedad
		if (_speed.getY() < SPEED_LIMIT)
			_speed += {0, GRAVITY};

		// Velocidad en este ciclo (no siempre avanza lateralmente)
		Vector2D<> realSpeed = _speed;

		// Intenta moverse
		Collision collision = tryToMove(realSpeed, Collision::PLAYER);

		// Si toca un objeto en horizontal cambia de dirección
		if (collision.horizontal)
			_speed.setX(-_speed.getX());

		// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
		if (collision.vertical)
			_speed.setY(0);
	}
}


Collision Enemy::hit(const SDL_Rect& region, Collision::Target target)
{
	Collision col;

	SDL_Rect enemyRect
	{
		_position.getX() + _speed.getX(), // se mueve en el mapa asiq ya se aplica el offset en el render
		_position.getY() + _speed.getY() - TILE_SIDE / 2, // para q atraviese un poco el collider
		TILE_SIDE,
		TILE_SIDE
	};

	// si hay colision, devolvemos true
	if (SDL_IntersectRect(&region, &enemyRect, &col.intersectionRect) && target == Collision::PLAYER)
	{
		col.result = Collision::DAMAGE;
	}

	if (!game->getMarioImmunity())
	{
		if (col.result == Collision::DAMAGE && target == Collision::PLAYER // si la colision es del player
			&& col.intersectionRect.y <= enemyRect.y // desde arriba
			&& col.intersectionRect.w > TILE_SIDE / 4) // para que no detecte col desde el lado
		{
			cout << "mario hace damage" << endl;
			_isAlive = false;
		}
		else if (col.result == Collision::DAMAGE && target == Collision::PLAYER)
		{
			//game->playerHit();
			cout << "mario recibe damage" << endl;
		}
	}
	return col;
}

SceneObject* Enemy::clone() const
{
	return nullptr;
}

void Enemy::updateAnim()
{
}
