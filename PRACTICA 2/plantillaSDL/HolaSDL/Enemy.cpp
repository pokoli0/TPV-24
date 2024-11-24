#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* game, int x, int y, Texture* t)
	: SceneObject(game, x, y, TILE_SIDE, TILE_SIDE, t)
{
	setScale(2);

	_speed.setX(-3);
}


void Enemy::update()
{
	checkAlive();

	collision = tryToMove(_speed, Collision::PLAYER);

	if (_speed.getY() < SPEED_LIMIT) _speed += {0, GRAVITY};

	if (collision.vertical) _speed.setY(0);
	if (collision.horizontal) _speed.setX(-_speed.getX()); // cambio de direccion

	if (_speed.getX() > 0) _flip = SDL_FLIP_NONE;
	else if (_speed.getX() < 0) _flip = SDL_FLIP_HORIZONTAL;
}


Collision Enemy::hit(const SDL_Rect& region, Collision::Target target)
{
	Collision col;
	//// Calcula la intersección
	//SDL_Rect intersection;
	//SDL_Rect ownRect = getCollisionRect();
	//SDL_IntersectRect(&ownRect, &region, &intersection);
	//
	//col = { Collision::NONE, intersection.w, intersection.h };

	//if (target == Collision::ENEMIES && col.horizontal > 0) 
	//{
	//	cout << "damage";
	//	return { Collision::DAMAGE, col.horizontal, col.vertical };
	//}


	return { Collision::NONE, col.horizontal, col.vertical };
}

SceneObject* Enemy::clone() const
{
	return nullptr;
}

