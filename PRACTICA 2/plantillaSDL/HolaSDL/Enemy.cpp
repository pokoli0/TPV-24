#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* game, int x, int y, Texture* t)
	: SceneObject(game, x, y, TILE_SIDE, TILE_SIDE, t)
{

}

void Enemy::render(SDL_Renderer* renderer)
{

}

Collision Enemy::hit(const SDL_Rect& region, Collision::Target target)
{
	return Collision();
}

SceneObject* Enemy::clone() const
{
	return nullptr;
}
