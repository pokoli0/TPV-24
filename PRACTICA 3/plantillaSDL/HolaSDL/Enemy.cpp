#include "checkML.h"

#include "Enemy.h"
#include "Game.h"

#include "PlayState.h"

Enemy::Enemy(Game* game, PlayState* s, int x, int y, Texture* t)
	: SceneObject(game, s, x, y, TILE_SIDE, TILE_SIDE, t)
{
	setScale(2);

	_speed.setX(-3);
}


void Enemy::update()
{
	collision = tryToMove(_speed, Collision::PLAYER);

	if (_speed.getY() < SPEED_LIMIT) _speed += {0, GRAVITY};

	if (collision.vertical) _speed.setY(0);
	if (collision.horizontal) _speed.setX(-_speed.getX()); // cambio de direccion

	if (_speed.getX() > 0) _flip = SDL_FLIP_HORIZONTAL;
	else if (_speed.getX() < 0) _flip = SDL_FLIP_NONE;

	checkAlive();
}


Collision Enemy::hit(const SDL_Rect& region, Collision::Target target)
{
	// Calcula la interseccion
	SDL_Rect intersection;
	SDL_Rect ownRect = getCollisionRect();
	bool hasIntersection = SDL_IntersectRect(&ownRect, &region, &intersection);

	if (hasIntersection) 
	{
		Collision collision{ Collision::DAMAGE, intersection.w, intersection.h };


		if (target == Collision::ENEMIES && !_playState->getMarioImmunity()) // si mario no es inmune
		{
			if (intersection.y <= ownRect.y // desde arriba
				&& intersection.w > TILE_SIDE / 4) // para que no detecte col desde el lado
			{
				delete this;
			}
			else // no entra siempre
			{
				cout << "col player" << endl;
				cout << _playState->getMarioImmunity() << endl;
				_playState->playerHit();
			}

			return collision;
		}
	}

	return Collision{ Collision::NONE }; // constante Collision{}
}

SceneObject* Enemy::clone() const
{
	return nullptr;
}

void Enemy::checkAlive()
{
	if (_position.getY() >= MAX_HEIGHT || _position.getX() <= 0 )
	{
		delete this; // ya no peta, habia q hacerlo al final del update
		cout << "Byebye" << endl;
	}
}

